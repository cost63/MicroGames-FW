#pragma once

#include "../graphics/VertexArray.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/RenderStates.h"
#include "../graphics/RenderEntity.h"

namespace mg
{

class Renderer
{
public:
    Renderer();
    ~Renderer();

    static void setupBuffers();

    void draw(const VertexArray& v, const RenderStates& states);

    void render();

private:
    static uint32_t s_VBO;
    static uint32_t s_VAO;

    static const uint32_t c_VBOSize = 10;
    Vertex* m_vertexBuffer;
    uint32_t m_vertexCount;

    RenderEntity m_entities[c_VBOSize];
    uint32_t m_entityCount;

    Matrix4 m_projection = ortho(0, 500, 400, 0);
};

} // namespace mg
