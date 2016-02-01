#include "CircleShape.h"

#include <cmath>

namespace mg {

CircleShape::CircleShape()
: m_radius(0.0)
, m_sagmentCount(32)
{
    m_vertices.resize(m_sagmentCount + 1);
    m_vertices.type = PrimitiveType::TriangleFan;
}

void CircleShape::setRadius(float radius) {
    m_radius = radius;

    updateVertices();
}

float CircleShape::getRadius() const {
    return m_radius;
}

void CircleShape::setSagmentCount(uint32_t count) {
    m_sagmentCount = count;
    m_vertices.resize(count + 1);

    updateVertices();
}

uint32_t CircleShape::getSagmentCount() const {
    return m_sagmentCount;
}

/* Private */

void CircleShape::updateVertices() {
    m_vertices[0].pos = Vec2f(0.0, 0.0);

    for(uint32_t i = 1; i < m_sagmentCount + 1; i++) {
        const float angle = ((float)i / (m_sagmentCount - 1)) * (3.1415926535897 * 2);

        Vec2f pos;
        pos.x = m_radius * std::cos(angle);
        pos.y = m_radius * std::sin(angle);

        m_vertices[i].pos = pos;
    }
}

} // namespace mg
