#pragma once

#include <../graphics/VertexArray.h>
#include "../graphics/ShaderProgram.h"
#include "../graphics/RenderStates.h"

namespace mg
{

struct RenderCommand
{
    RenderStates states;
    PrimitiveType type;
    uint32_t vertexIndex = 0;
    uint32_t vertexCount = 0;
};

class Renderer
{
public:
    Renderer();

    static void setupBuffers();

    void draw(const VertexArray& v, const RenderStates& states);

    void render();

private:
    static uint32_t s_VBO;
    static uint32_t s_VAO;

    static const uint32_t c_VBOSize = 65536;
    Vertex m_vertexBuffer[c_VBOSize];
    uint32_t m_vertexCount;

    RenderCommand m_commands[512];
    uint32_t m_commandCount;
};

} // namespace mg
