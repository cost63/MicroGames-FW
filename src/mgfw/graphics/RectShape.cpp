#include "RectShape.h"

namespace mg {

RectShape::RectShape()
{
    m_vertices.type = PrimitiveType::Quads;
    m_vertices.resize(4);
}

/* Private */

void RectShape::onSizeChange(const Vec2f& prevSize) {
    // Set vertices based on the transform size
    m_vertices[1].pos.x = m_size.x;
    m_vertices[2].pos   = m_size;
    m_vertices[3].pos.y = m_size.y;
}

} // namespace mg
