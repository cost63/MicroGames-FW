#include "Renderer.h"

#include <cstring>

#include "../graphics/OpenGL.h"
#include "../graphics/Vertex.h"
#include "../math/Vector3.h"

namespace mg
{

Renderer::Renderer()
: s_VAO(0)
, s_VBO(0)
, m_vertexCount(0)
, m_entityCount(0)
{}

Renderer::~Renderer()
{
    delete[] m_vertexBuffer;
}

void Renderer::draw(const VertexArray& v, const RenderStates& states)
{
    RenderEntity entity;

    // Setup the command
    entity.type = v.type;
    entity.states = states;
    entity.vertexCount = v.size();
    entity.vertexIndex = m_vertexCount;

    // Copy vertex data to the vertex storage
    memcpy(m_vertexBuffer + m_vertexCount, v.data(), sizeof(Vertex) * entity.vertexCount);

    m_vertexCount += entity.vertexCount;

    // Store command in the command storage
    m_entities[m_entityCount++] = entity;
}

void Renderer::render()
{
    // Update buffer with vertices
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, nullptr, GL_DYNAMIC_DRAW);
    void* buff = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(buff, m_vertexBuffer, sizeof(Vertex) * m_vertexCount);
    glUnmapBuffer(GL_ARRAY_BUFFER);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_vertexCount, &m_vertexBuffer);

    glBindVertexArray(s_VAO);

    for(uint32_t i = 0; i < m_entityCount; i++)
    {
        RenderEntity& entity = m_entities[i];

        ShaderProgram* shader = entity.states.shader;

        if(shader)
        {
            shader->use();
            shader->setUniform("projection",m_projection);
            shader->setUniform("transform",entity.states.transform);
        }

        glDrawArrays(GL_TRIANGLES, entity.vertexIndex, entity.vertexCount);
    }

    m_vertexCount = 0;
    m_entityCount = 0;
}

void Renderer::setViewSize(const Vec2i& size)
{
    m_projection = ortho(0, size.w, size.h, 0);
}

/* Protected */

void Renderer::setupBuffers()
{
    m_vertexBuffer = new Vertex[ c_VBOSize ];

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
