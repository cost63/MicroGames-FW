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
    RenderEntity entity;

    // Setup entity
    entity.type = vertices.type;
    entity.states = states;
    entity.normalized = vertices.normalized;
    entity.vertexCount = vertices.size();
    entity.vertexIndex = m_vertexCount;

    // If the primitive type is quad, convert its vertices to 2 triangles
    if(vertices.type == PrimitiveType::Quads) {
        // Override the entity attributes
        entity.type = PrimitiveType::Triangles;
        entity.vertexCount = ( vertices.size() / 4 ) * 6;

        uint32_t totalQuads = vertices.size() / 4;

        // Go trough each quad in the vertex arraay
        for(uint32_t i = 0; i < totalQuads; i++) {
            const Vertex& v0 = vertices[i + 0];
            const Vertex& v1 = vertices[i + 1];
            const Vertex& v2 = vertices[i + 2];
            const Vertex& v3 = vertices[i + 3];

            // Setup two triangles
            const Vertex quadVertices[] = {
                v0, v1, v2,
                v2, v3, v0,
            };

            // Copy triangle vertex data to the vertex storage
            memcpy(m_vertexBuffer.data() + m_vertexCount, quadVertices, sizeof(Vertex) * 6);
            m_vertexCount += 6;
        }
    }
    else {
        // Copy vertex data to the vertex storage
        memcpy(m_vertexBuffer.data() + m_vertexCount, vertices.data(), sizeof(Vertex) * entity.vertexCount);
        m_vertexCount += entity.vertexCount;
    }

    // Store command in the command storage
    m_entities[m_entityCount++] = entity;
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

    // Update buffer with vertices
    void* buff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(buff, m_vertexBuffer.data(), sizeof(Vertex) * m_vertexCount);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Bind the vertex array
    glBindVertexArray(s_VAO);

    // Go trough each render entity
    for(uint32_t i = 0; i < m_entityCount; i++) {
        RenderEntity& entity = m_entities[i];

        ShaderProgram* shader = entity.states.shader;

        // If there was no custom shader specified, use default one
        if(!shader) {
            shader = &m_defShaderProgram;
        }

        // Apply shader
        shader->use();
        shader->setUniform("transform", entity.states.transform);

        // Check if projection should be used
        if(entity.normalized) {
            shader->setUniform("projection", Matrix4());
        }
        else {
            shader->setUniform("projection", m_projection);
        }

        if(entity.states.texture) {
            // Check if new texture was provided
            uint32_t tHandle = entity.states.texture->getHandle();

            if(m_lastTextureHandle != tHandle) {
                entity.states.texture->bind();
                m_lastTextureHandle = tHandle;
            }


            shader->setUniform("texture", 0);
            shader->setUniform("hasTexture", true);
        }

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

    /* Setup default shaders */
    if(!m_defShaderProgram.loadFromFile(
            "src/mgfw/graphics/shaders/default.vert",
            "src/mgfw/graphics/shaders/default.frag"))
    {
        PRINT_ERROR("Renderer failed to initialize default shader");
    }

    /* Setup view */
    m_projection = ortho(0, viewSize.w, viewSize.h, 0);
}

/* Private */

void Renderer::updateView() {
    float aspect = m_viewSize.w / m_viewSize.h;

    int width = m_viewSize.h * aspect;
    int left = ( m_viewSize.w - width ) / 2;

    glViewport(left, 0, width, m_viewSize.h);

    if(!m_isViewRelative) {
        m_projection = ortho(0, m_viewSize.w, m_viewSize.h, 0);
    }
}

} // namespace mg
