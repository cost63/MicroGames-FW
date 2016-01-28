#include "Vertex.h"

namespace mg {

Vertex::Vertex(const Vec2f& _pos /*= Vec2f() */,
               const Color& _color /* = Color::White */,
               const Vec2f& _texCoord /* = Vec2f() */
               )
: pos(_pos)
, color(_color)
, texCoord(_texCoord)
{}

std::ostream& operator<<( std::ostream& os, const Vertex& v ) {
    return os << v.pos << " " << v.color;
}

} // namespace mg
