#include "Renderer.h"

#include <cstring>

#include "../graphics/OpenGL.h"
#include "../graphics/Vertex.h"
#include "../math/Vector3.h"

namespace mg
{

uint32_t Renderer::s_VAO = 0;
uint32_t Renderer::s_VBO = 0;

Renderer::Renderer()
: m_vertexCount(0)
, m_commandCount(0)
{}

void Renderer::setupBuffers()
{
//    const float quadVerts[] = {
//        -0.5,  0.5,  0.0,
//         0.5,  0.5,  0.0,
//         0.5, -0.5,  0.0,
//        -0.5, -0.5,  0.0,
//    };
//
//    const uint32_t quadIndices[] = {
//        0, 1, 3,    // #1 Triangle
//        1, 2, 3,    // #2 Triangle
//    };

//    uint32_t quadVBO = 0;
//    uint32_t quadEBO = 0;

//    // Generate buffers
//    glGenVertexArrays(1, &s_quadVAO);
//    glGenBuffers( 1, &quadVBO);
//    glGenBuffers( 1, &quadEBO);
//
//    // Bind VAO
//    glBindVertexArray(s_quadVAO);
//
//    // Bind VBO and set vertex data
//    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
//
//    // Bind EBO and set index data
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), nullptr);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);

    glBindVertexArray(s_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, c_VBOSize, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::draw(const VertexArray& v, const RenderStates& states)
{
    RenderCommand cmd;

    // Setup the command
    cmd.type = v.type;
    cmd.vertexCount = v.size();
    cmd.vertexIndex = m_vertexCount;

    // Copy vertex data to the vertex storage
    memcpy(m_vertexBuffer + m_vertexCount, v.data(), sizeof(Vertex) * cmd.vertexCount);

    m_vertexCount += cmd.vertexCount;

    // Store command in the command storage
    m_commands[m_commandCount++] = cmd;
}

void Renderer::render()
{
    // Update buffer with vertices
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_vertexCount, m_vertexBuffer);

    glBindVertexArray(s_VAO);

    for(uint32_t i = 0; i < m_commandCount; i++)
    {
        RenderCommand& cmd = m_commands[i];

        const ShaderProgram* shader = cmd.states.shader;

        if(shader)
        {
            shader->use();
        }

        glDrawArrays(GL_TRIANGLES, cmd.vertexIndex, cmd.vertexCount);
    }

    m_vertexCount = 0;
    m_commandCount = 0;
}

} // namespace mg
