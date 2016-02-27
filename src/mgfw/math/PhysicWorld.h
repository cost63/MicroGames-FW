#pragma once

#include <Box2D/Box2D.h>

#include "../math/Vector2.h"
#include "../system/Time.h"

namespace mg {

class ShapePhysic;

class PhysicWorld {
public:
    PhysicWorld();
    PhysicWorld(const Vec2f& gravity);

    void draw();

    void addPhysicShape(ShapePhysic& shape);

    void update(const Time& delta);

    void* getHandle();

private:
    b2World m_handle;

    int m_velocityIter;
    int m_positionIter;

};

} // namespace mg
