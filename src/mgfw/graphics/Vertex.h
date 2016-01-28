#pragma once

#include "../math/Vector2.h"
#include "../graphics/Color.h"

namespace mg {

struct Vertex {
    Vec2f pos;
    Color color;
    Vec2f texCoord;

    Vertex(const Vec2f& pos = Vec2f(),
           const Color& color = Color::White,
           const Vec2f& texCoord = Vec2f()
           );
};

#include <iostream>
std::ostream& operator<<( std::ostream& os, const Vertex& v );

} // namespace mg
