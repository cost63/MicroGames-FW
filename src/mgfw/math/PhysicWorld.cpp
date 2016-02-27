#include "PhysicWorld.h"

#include "../math/ShapePhysic.h"

namespace mg {

PhysicWorld::PhysicWorld()
: m_handle{ b2Vec2(0, 0) }
, m_velocityIter(6)
, m_positionIter(2)
{}

PhysicWorld::PhysicWorld(const Vec2f& gravity)
: m_handle{ b2Vec2(gravity.x, gravity.y) }
, m_velocityIter(6)
, m_positionIter(2)
{}

void PhysicWorld::addPhysicShape(ShapePhysic& shape) {
    shape.addToWorld(*this);
}

void PhysicWorld::update(const Time& delta) {
    m_handle.Step(delta.asSeconds(), m_velocityIter, m_positionIter);
}

void* PhysicWorld::getHandle() {
    return &m_handle;
}

} // namespace mg
