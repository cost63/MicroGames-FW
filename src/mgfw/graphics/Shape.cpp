#include "Shape.h"

#include "../system/ErrorLog.h"

#define PI 3.1415926535897

namespace mg {

Shape::Shape()
: m_texture(nullptr)
{
    // This is important for correct transform calculation
    // because shapes do not work with transformable's size
//    m_size = Vec2f(1.0, 1.0);
}

void Shape::draw(Renderer& renderer, RenderStates states) const {
    states.transform *= getTransform();

    if(m_texture) {
        states.texture = m_texture;
    }

    renderer.draw(m_vertices, states);
}

void Shape::setColor(const Color& color) {
    m_color = color;

    m_vertices.setColor(color);
}

void Shape::setColor(const Color& color, uint32_t index) {
    if(index < m_vertices.size()) {
        m_vertices[index].color = color;
    }
    #ifdef MGFW_DEBUG
    else {
        priv::logError(
                "Unable to set vertex color at " + std::to_string(index) +
                " because vertex array size is " + std::to_string(m_vertices.size()),
                priv::c_prefWarning
        );
    }
    #endif // MGFW_DEBUG
}

Color Shape::getColor() const {
    return m_color;
}

void Shape::setTexture(const Texture* texture) {
    m_texture = texture;
}

const Texture* Shape::getTexture() const {
    return m_texture;
}

void Shape::setUnitMode(UnitMode mode) {
    m_vertices.unitMode = mode;
}

UnitMode Shape::getUnitMode() const {
    return m_vertices.unitMode;
}

VertexArray& Shape::getVertices() {
    return m_vertices;
}

const VertexArray& Shape::getVertices() const {
    return m_vertices;
}

} // namespace mg
