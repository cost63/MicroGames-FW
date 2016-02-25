#pragma once

#include <Box2D/Box2D.h>

#include "../math/Vector2.h"

namespace mg {
namespace priv {

template <typename T>
b2Vec2 getBox2dVec(const Vector2<T>& v) {
    return b2Vec2(v.x, v.y);
}

Vec2f getVec2fFromBox2D(const b2Vec2& v);

} // namespace priv
} // namespace mg





