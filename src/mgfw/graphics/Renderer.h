#pragma once

#include <vector>

#include "../math/Vector2.h"
#include "../math/Matrix4.h"
#include "../graphics/Vertex.h"
#include "../graphics/RenderEntity.h"
#include "../graphics/ShaderProgram.h"

namespace mg {

/* Forward declarations */
struct RenderStates;
struct VertexArray;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const VertexArray& v);
    void draw(const VertexArray& v, const RenderStates& states);

    void render();

    void setViewSize(const Vec2i& size);

protected:
    void setupRenderer();

private:
    // Vertex buffer IDs
    uint32_t s_VAO;
    uint32_t s_VBO;

    // Vertex buffer
    const uint32_t c_VBOSize = 65536;
    std::vector<Vertex> m_vertexBuffer;
    uint32_t m_vertexCount;

    // Render entity buffer
    std::vector<RenderEntity> m_entities;
    uint32_t m_entityCount;

    ShaderProgram m_defShaderProgram;

    // Projection
    // TODO(Smeky) Add support for window resizing and projection change
    Matrix4 m_projection = ortho(0, 1000, 700, 0);
};

} // namespace mg
