#include "RectShapePhysic.h"

#include "../system/ErrorLog.h"
#include "../math/PhysicWorld.h"

namespace mg {

RectShapePhysic::RectShapePhysic()
{
    m_vertices.type = PrimitiveType::Quads;
    m_vertices.resize(4);
}

void RectShapePhysic::addToWorld(PhysicWorld& world) {
    if(!m_handle) {
        b2BodyDef definition;
        definition.type = getB2Type(m_rigidType);
        definition.position.Set(
                m_pos.x + m_size.w / 2,
                m_pos.y + m_size.h / 2
        );

        m_handle = ((b2World*)(world.getHandle()))->CreateBody(&definition);

        b2PolygonShape fixture;
        fixture.SetAsBox(
                m_size.x / 2,
                m_size.y / 2
        );

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

/* Private */

void RectShapePhysic::onSizeChange(const Vec2f& prevSize) {
    m_vertices[1].pos.x = m_size.x;
    m_vertices[2].pos   = m_size;
    m_vertices[3].pos.y = m_size.y;

    if(m_handle) {
        b2PolygonShape fixture;
        fixture.SetAsBox(
                m_size.x / 2,
                m_size.y / 2
        );

        m_handle->CreateFixture(&fixture, 0.0);
    }
}

} // namespace mg
