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

    void setViewSize(const Vec2f& size);

    // Tell the renderer to scale its content relative to the view size
    void setRelativeViewEnabled(bool enabled);
    bool isRelativeViewEnabled() const;

protected:
    void setupRenderer(const Vec2f& viewSize);

private:
    void updateView();

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

    // Default shader
    ShaderProgram m_defShaderProgram;

    // Projection
    bool m_isViewRelative;
    Vec2f m_viewSize;
    Matrix4 m_projection;
};

} // namespace mg
