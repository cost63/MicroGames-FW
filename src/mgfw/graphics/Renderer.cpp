#include "Renderer.h"

#include "../graphics/OpenGL.h"
#include "../graphics/Vertex.h"
#include "../math/Vector3.h"

namespace mg
{

uint32_t Renderer::s_quadVAO = 0;

Renderer::Renderer()
{}

void Renderer::setupBuffers()
{
    const float quadVerts[] = {
        -0.5,  0.5,  0.0,
         0.5,  0.5,  0.0,
         0.5, -0.5,  0.0,
        -0.5, -0.5,  0.0,
    };

    const uint32_t quadIndices[] = {
        0, 1, 3,    // #1 Triangle
        1, 2, 3,    // #2 Triangle
    };

    uint32_t quadVBO = 0;
    uint32_t quadEBO = 0;

    // Generate buffers
    glGenVertexArrays(1, &s_quadVAO);
    glGenBuffers( 1, &quadVBO);
    glGenBuffers( 1, &quadEBO);

    // Bind VAO
    glBindVertexArray(s_quadVAO);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

    // Bind EBO and set index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw(ShaderProgram& shader)
{
    shader.use();

    glBindVertexArray(s_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

} // namespace mg
