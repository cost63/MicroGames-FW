#include "PhysicWorld.h"

#include "../math/PhysicRect.h"

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

void PhysicWorld::addPhysicShape(PhysicRect& shape) {
    shape.addToWorld(m_handle);
}

void PhysicWorld::update(const Time& delta) {
    m_handle.Step(delta.asSeconds(), m_velocityIter, m_positionIter);
}

} // namespace mg
