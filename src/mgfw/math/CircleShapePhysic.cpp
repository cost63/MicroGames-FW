#include "CircleShapePhysic.h"

#include "../system/ErrorLog.h"
#include "../math/PhysicWorld.h"

namespace mg {

CircleShapePhysic::CircleShapePhysic()
: m_radius(0.0)
, m_sagmentCount(32)
{
    m_vertices.resize(m_sagmentCount + 1);
    m_vertices.type = PrimitiveType::TriangleFan;
}

void CircleShapePhysic::addToWorld(PhysicWorld& world) {
    if(!m_handle) {
        b2BodyDef definition;
        definition.type = getB2Type(m_rigidType);
        definition.position.Set(
                m_pos.x,
                m_pos.y
        );

        m_handle = ((b2World*)(world.getHandle()))->CreateBody(&definition);

        b2CircleShape fixture;
        fixture.m_radius = m_radius;

        m_size = Vec2f(0.0);

        m_handle->CreateFixture(&fixture, m_density);
    }
    #ifdef MGFW_DEBUG
    else {
        priv::logError(
                "Tried to add the same object into the physics world twice.",
                priv::c_prefWarning
        );
    }
    #endif // MGFW_DEBUG
}

void CircleShapePhysic::setRadius(float radius) {
    m_radius = radius;

    updateVertices();
}

float CircleShapePhysic::getRadius() const {
    return m_radius;
}

void CircleShapePhysic::setSagmentCount(uint32_t count) {
    m_sagmentCount = count;
    m_vertices.resize(count + 1);

    updateVertices();
}

uint32_t CircleShapePhysic::getSagmentCount() const {
    return m_sagmentCount;
}

/* Private */

void CircleShapePhysic::updateVertices() {
    m_vertices[0].pos = Vec2f(0.0, 0.0);

    for(float i = 1; i < m_sagmentCount + 1; i++) {
        const float angle = (i / (m_sagmentCount - 1)) * (3.1415926535897 * 2);

        Vec2f pos;
        pos.x = m_radius * std::cos(angle);
        pos.y = m_radius * std::sin(angle);

        m_vertices[i].pos = pos;
    }
}

} // namespace mg
