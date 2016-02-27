#include "Renderer.h"

#include <cstring>

#include "../system/ErrorLog.h"
#include "../graphics/OpenGL.h"
#include "../graphics/VertexArray.h"
#include "../graphics/Texture.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/RenderStates.h"
#include "../graphics/RenderEntity.h"
#include "../math/Vector3.h"

namespace mg {

Renderer::Renderer()
: s_VAO(0)
, s_VBO(0)
, m_vertexCount(0)
, m_entityCount(0)
, m_lastTextureHandle(0)
, m_isViewRelative(true)
{}

Renderer::~Renderer() {
    glDeleteBuffers(1, &s_VBO);
    glDeleteVertexArrays(1, &s_VAO);
}

void Renderer::draw(const Drawable& drawable, const RenderStates& states /* = RenderStates() */) {
    drawable.draw(*this, states);
}

void Renderer::draw(const VertexArray& vertices, const RenderStates& states /* = RenderStates() */) {
    if(vertices.type == PrimitiveType::Quads) {
        batchQuads(vertices, states);
    }
    else {
        batchVertices(vertices, states);
    }
}

void Renderer::render() {
    const uint32_t mode[] = {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_LINE_LOOP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
    };

    // Bind the VBO so we can update its data
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);

    // Upload batched vertices to the buffer
    void* buff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(buff, m_vertexBuffer.data(), sizeof(Vertex) * m_vertexCount);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Bind the vertex array
    glBindVertexArray(s_VAO);

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Go trough each render entity
    for(uint32_t i = 0; i < m_entityCount; i++) {
        const RenderEntity& entity = m_entities[i];

        applyShader(entity);
        applyTexture(entity);

        // Draw current vertex pack in the batch
        glDrawArrays(mode[(int)entity.type], entity.vertexIndex, entity.vertexCount);
    }

    m_vertexCount = 0;
    m_entityCount = 0;
}

void Renderer::setViewSize(const Vec2f& size) {
    // Prevent pointless calculations
    if(m_viewSize != size) {
        m_viewSize = size;

        updateView();
    }
}

void Renderer::setRelativeViewEnabled(bool enabled) {
    m_isViewRelative = enabled;
}

bool Renderer::isRelativeViewEnabled() const {
    return m_isViewRelative;
}

/* Protected */

void Renderer::setupRenderer(const Vec2f& viewSize) {
    /* Setup buffers */
    m_vertexBuffer.resize(c_VBOSize);
    m_entities.resize(c_VBOSize);

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);

    glBindVertexArray(s_VAO);

    // Initialize VBO with empty data
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, c_VBOSize, nullptr, GL_DYNAMIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (const GLvoid*)sizeof(Vec2f) );
    glEnableVertexAttribArray(1);
    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (const GLvoid*)(sizeof(Vec2f) + sizeof(Color)));
    glEnableVertexAttribArray(2);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Setup default shader program
    if(!m_defShaderProgram.loadFromFile(
            "src/mgfw/graphics/shaders/default.vert",
            "src/mgfw/graphics/shaders/default.frag"))
    {
        priv::logError("Renderer failed to initialize default shader");
    }

    // Setup view
    m_projection = ortho(0, viewSize.w / 50, viewSize.h / 50, 0);
    m_pixelProjection = ortho(0, viewSize.w, viewSize.h, 0);
}

/* Private */

void Renderer::updateView() {
    float aspect = m_viewSize.w / m_viewSize.h;

    int width = m_viewSize.h * aspect;
    int left = ( m_viewSize.w - width ) / 2;

    glViewport(left, 0, width, m_viewSize.h);

    if(!m_isViewRelative) {
        m_projection = ortho(0, m_viewSize.w / 50, m_viewSize.h / 50, 0);
        m_pixelProjection = ortho(0, m_viewSize.w, m_viewSize.h, 0);
    }
}

void Renderer::batchVertices(const VertexArray& vertices, const RenderStates& states) {
    // Make sure not vertex array size is less then buffer size
    if(vertices.size() >= c_VBOSize) {
        priv::logError("VertexArray size exceeded vertex buffer size");
        return;
    }

    RenderEntity entity;

    // Setup entity
    entity.type         = vertices.type;
    entity.states       = states;
    entity.unitMode     = vertices.unitMode;
    entity.vertexCount  = vertices.size();
    entity.vertexIndex  = m_vertexCount;

    // Buffer is full, render everything in it and make it empty
    if(m_vertexCount + entity.vertexCount >= c_VBOSize) {
        render();
    }

    // Copy vertex data to the vertex storage
    memcpy(m_vertexBuffer.data() + m_vertexCount, vertices.data(), sizeof(Vertex) * entity.vertexCount);
    m_vertexCount += entity.vertexCount;

    // Store command in the command storage
    m_entities[m_entityCount++] = entity;
}

void Renderer::batchQuads(const VertexArray& vertices, const RenderStates& states) {
    // Calculate amount of triangle vertices as we will convert quads to triangles
    const uint32_t triangleVertexCount = ( vertices.size() / 4 ) * 6;

    // Make sure not vertex array size is less then buffer size
    if(triangleVertexCount >= c_VBOSize) {
        priv::logError("VertexArray size exceeded vertex buffer size");
        return;
    }

    RenderEntity entity;

    // Setup entity
    entity.type         = PrimitiveType::Triangles;
    entity.states       = states;
    entity.unitMode     = vertices.unitMode;
    entity.vertexCount  = triangleVertexCount;
    entity.vertexIndex  = m_vertexCount;

    // Buffer is full, render everything in it and make it empty
    if(m_vertexCount + entity.vertexCount >= c_VBOSize) {
        render();
    }

    /* Convert quad vertices to triangles */
    uint32_t totalQuads = vertices.size() / 4;

    // TODO(Smeky) Add support for vertex index buffer
    //      -> Should reduce amount of batched vertices significantly
    //      -> Requires using the IBO for all primitive types as well, otherwise rendering order wouldn't work
    // Go trough each quad in the vertex array
    for(uint32_t i = 0; i < totalQuads * 4; i += 4) {
        const Vertex& v0 = vertices[i + 0];
        const Vertex& v1 = vertices[i + 1];
        const Vertex& v2 = vertices[i + 2];
        const Vertex& v3 = vertices[i + 3];

        // Setup two triangles
        const Vertex quadVertices[] = {
            v0, v1, v2,
            v2, v3, v0,
        };

        // Copy triangles to the vertex storage
        memcpy(m_vertexBuffer.data() + m_vertexCount, quadVertices, sizeof(Vertex) * 6);
        m_vertexCount += 6;
    }

    // Store entity in the entity buffer
    m_entities[m_entityCount++] = entity;
}

void Renderer::applyShader(const RenderEntity& entity) {
    const ShaderProgram* shader = entity.states.shader;

    // If there was no custom shader specified, use the default one
    if(!shader) {
        shader = &m_defShaderProgram;
    }

    // Bind the shader program
    shader->use();

    // Set transform uniform
    shader->setUniform("transform", entity.states.transform);

    // Set projection uniform based on unit mode
    switch(entity.unitMode) {
    case UnitMode::Meter:       shader->setUniform("projection", m_projection); break;
    case UnitMode::Pixel:       shader->setUniform("projection", m_pixelProjection); break;
    case UnitMode::Normalized:  shader->setUniform("projection", Matrix4()); break;
    default: break;
    }

    // Set texture uniform, if there's one
    if(entity.states.texture) {
        shader->setUniform("texture", 0);
        shader->setUniform("hasTexture", true);
    }
    else {
        shader->setUniform("hasTexture", false);
    }
}

void Renderer::applyTexture(const RenderEntity& entity) {
    if(entity.states.texture) {
        uint32_t tHandle = entity.states.texture->getHandle();

        // Check if new texture was provided
        if(m_lastTextureHandle != tHandle) {
            // Bind the texture
            entity.states.texture->bind();

            // Store its handle so we don't bind the same texture twice
            m_lastTextureHandle = tHandle;
        }
    }
    else {
        glBindTexture(GL_TEXTURE_2D, 0);
        m_lastTextureHandle = 0;
    }
}

} // namespace mg
