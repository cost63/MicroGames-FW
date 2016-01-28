#pragma once

#include "../math/Vector2.h"
#include "../math/Matrix4.h"
#include "../graphics/Vertex.h"
#include "../graphics/RenderEntity.h"

namespace mg {

/* Forward declarations */
struct RenderStates;
struct VertexArray;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const VertexArray& v, const RenderStates& states);

    void render();

    void setViewSize(const Vec2i& size);

protected:
    void setupBuffers();

private:
    uint32_t s_VAO;
    uint32_t s_VBO;

    const uint32_t c_VBOSize = 10;
    Vertex* m_vertexBuffer;
    uint32_t m_vertexCount;

    RenderEntity m_entities[10];
    uint32_t m_entityCount;

    Matrix4 m_projection = ortho(0, 500, 400, 0);
};

} // namespace mg
