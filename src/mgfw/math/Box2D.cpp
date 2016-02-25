#include "Box2D.h"

namespace mg {
namespace priv {

Vec2f getVec2fFromBox2D(const b2Vec2& v) {
    return Vec2f(v.x, v.y);
}

} // namespace priv
} // namespace mg
