#include "Shape.h"

namespace mg {

Shape::Shape()
{}

void Shape::draw(Renderer& renderer, RenderStates states) const {
    states.transform *= getMatrix();

    if(m_texture) {
        states.texture = m_texture;
    }

    renderer.draw(m_vertices, states);
}

void Shape::setColor(const Color& color) {
    m_color = color;

    for(uint32_t i = 0; i < m_vertices.size(); i++) {
        m_vertices[i].color = color;
    }
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

VertexArray& Shape::getVertices() {
    return m_vertices;
}

const VertexArray& Shape::getVertices() const {
    return m_vertices;
}

} // namespace mg
