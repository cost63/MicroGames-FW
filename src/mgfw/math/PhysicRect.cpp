#include "PhysicRect.h"

#include "../system/ErrorLog.h"

namespace mg {

PhysicRect::PhysicRect()
: m_handle(nullptr)
{}

PhysicRect::~PhysicRect()
{}

void PhysicRect::addToWorld(b2World& world) {
    if(!m_handle) {
        b2BodyDef definition;
        definition.type = b2_dynamicBody;
        definition.position.Set(m_pos.x / 50, m_pos.y / 50);

        m_handle = world.CreateBody(&definition);

        b2PolygonShape fixture;
        fixture.SetAsBox((m_size.x / 50) / 2, (m_size.y / 50) / 2);

        m_handle->CreateFixture(&fixture, 0.0);
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

void PhysicRect::applyForceCenter(const Vec2f& force) {
    if(m_handle) {
        m_handle->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
    }
}

Matrix4 PhysicRect::getTransform() const {
    if(!m_handle) {
        return Matrix4();
    }

    const b2Vec2 pos = m_handle->GetPosition();

    if(pos.x != m_prevPos.x || pos.y != m_prevPos.y) {
        const float angle = -m_rotation * (3.1415926535897 / 180);
        const float c = std::cos(angle);
        const float s = std::sin(angle);

        const Vec2f scaleCos(m_scale.x * c, m_scale.y * c);
        const Vec2f scaleSin(m_scale.x * s, m_scale.y * s);

        const Vec2f translation(
                -m_origin.x * scaleCos.x - m_origin.y * scaleSin.y + pos.x * 50,
                 m_origin.x * scaleSin.x - m_origin.y * scaleCos.y + pos.y * 50
        );

        m_matrix = Matrix4(
                { +scaleCos.x, scaleSin.y, 0.0, translation.x },
                { -scaleSin.x, scaleCos.y, 0.0, translation.y },
                {  0.0,        0.0,        1.0, 0.0 },
                {  0.0,        0.0,        0.0, 1.0 }
        );

        m_prevPos = priv::getVec2fFromBox2D(pos);
    }

    return m_matrix;
}

/* Private */

void PhysicRect::onPosChange(const Vec2f& prevPos) {
    if(m_handle) {
        m_handle->SetTransform(priv::getBox2dVec(m_pos / 50), getRotationRad());
    }
}

void PhysicRect::onSizeChange(const Vec2f& prevSize) {
    m_vertices[1].pos.x = m_size.x;
    m_vertices[2].pos   = m_size;
    m_vertices[3].pos.y = m_size.y;

    if(m_handle) {
        b2PolygonShape fixture;
        fixture.SetAsBox((m_size.x / 50) / 2, (m_size.y / 50) / 2);

        m_handle->CreateFixture(&fixture, 0.0);
    }
}

void PhysicRect::onOriginChange(const Vec2f& prevOrigin) {

}

void PhysicRect::onRotationChange(float prevRotation) {
    if(m_handle) {
        m_handle->SetTransform(priv::getBox2dVec(m_pos / 50), getRotationRad());
    }
}

} // namespace mg
