#include "Renderer.h"

#include <cstring>

#include "../graphics/OpenGL.h"
#include "../graphics/VertexArray.h"
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
{}

Renderer::~Renderer() {
    glDeleteBuffers(1, &s_VBO);
    glDeleteVertexArrays(1, &s_VAO);
}

void Renderer::draw(const VertexArray& v, const RenderStates& states) {
    RenderEntity entity;

    // Setup the command
    entity.type = v.type;
    entity.states = states;
    entity.vertexCount = v.size();
    entity.vertexIndex = m_vertexCount;

    // If the primitive type is quad, convert its vertices to 2 triangles
    if(v.type == PrimitiveType::PType_Quads) {
        // Override the vertex count
        entity.vertexCount = ( v.size() / 4 ) * 6;

        uint32_t totalQuads = v.size() / 4;

        // Go trough each quad in the vertex arraay
        for(uint32_t i = 0; i < totalQuads; i++) {
            const Vertex& v0 = v[i + 0];
            const Vertex& v1 = v[i + 1];
            const Vertex& v2 = v[i + 2];
            const Vertex& v3 = v[i + 3];

            // Setup two triangles
            const Vertex vertices[] = {
                v0, v1, v2,
                v2, v3, v0,
            };

            // Copy triangle vertex data to the vertex storage
            memcpy(m_vertexBuffer.data() + m_vertexCount, vertices, sizeof(Vertex) * 6);
            m_vertexCount += 6;
        }
    }
    else {
        // Copy vertex data to the vertex storage
        memcpy(m_vertexBuffer.data() + m_vertexCount, v.data(), sizeof(Vertex) * entity.vertexCount);
        m_vertexCount += entity.vertexCount;
    }

    // Store command in the command storage
    m_entities[m_entityCount++] = entity;
}

void Renderer::render() {
    // Bind the VBO so we can update its data
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);

    // Update buffer with vertices
    void* buff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(buff, m_vertexBuffer.data(), sizeof(Vertex) * m_vertexCount);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glPolygonMode(GL_FRONT, GL_TRIANGLES);
    glPolygonMode(GL_BACK, GL_TRIANGLES);

    glBindVertexArray(s_VAO);

    for(uint32_t i = 0; i < m_entityCount; i++) {
        RenderEntity& entity = m_entities[i];

        ShaderProgram* shader = entity.states.shader;

        if(shader) {
            shader->use();
            shader->setUniform("projection",m_projection);
            shader->setUniform("transform",entity.states.transform);
        }

        glDrawArrays(GL_TRIANGLES, entity.vertexIndex, entity.vertexCount);
    }

    m_vertexCount = 0;
    m_entityCount = 0;
}

void Renderer::setViewSize(const Vec2i& size) {
    m_projection = ortho(0, size.w, size.h, 0);
}

/* Protected */

void Renderer::setupBuffers() {
    m_vertexBuffer.resize(c_VBOSize);
    m_entities.resize(c_VBOSize);

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);

    glBindVertexArray(s_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, c_VBOSize, nullptr, GL_DYNAMIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (const GLvoid*)sizeof(Vec2f) );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace mg
