#pragma once

#include <vector>

#include "../math/Vector2.h"
#include "../math/Matrix4.h"
#include "../graphics/Vertex.h"
#include "../graphics/RenderEntity.h"
#include "../graphics/ShaderProgram.h"

namespace mg {

/* Forward declarations */
class Drawable;

struct RenderStates;
struct VertexArray;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const Drawable& drawable, const RenderStates& states = RenderStates());
    void draw(const VertexArray& vertices, const RenderStates& states = RenderStates());

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
    Matrix4 m_projection = ortho(0, 600, 450, 0);
};

} // namespace mg
