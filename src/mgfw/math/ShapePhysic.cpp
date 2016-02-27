#include "ShapePhysic.h"

#include "../system/ErrorLog.h"

namespace mg {

// Returns equivalent rigid body type in box2d version
b2BodyType getB2Type(PhysicType type) {
    b2BodyType result = b2_staticBody;

    switch(type) {
    case PhysicType::Static:    result = b2_staticBody; break;
    case PhysicType::Dynamic:   result = b2_dynamicBody; break;
    case PhysicType::Kinematic: result = b2_kinematicBody; break;
    default: break;
    }

    return result;
}

ShapePhysic::ShapePhysic()
: m_handle(nullptr)
, m_rigidType(PhysicType::Static)
{}

void ShapePhysic::draw(Renderer& renderer, RenderStates states) const {
    if(m_handle) {
        Shape::draw(renderer, states);
    }
    #ifdef MGFW_DEBUG
    else {
        priv::logError(
                "Unable to draw physical shape that isn't in the physical world",
                priv::c_prefWarning
        );
    }
    #endif // MGFW_DEBUG
}

void ShapePhysic::applyForceCenter(const Vec2f& force) {
    if(m_handle) {
        m_handle->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
    }
}

void ShapePhysic::applyTorque(float torque) {
    if(m_handle) {
        m_handle->ApplyTorque(torque, true);
    }
}

void ShapePhysic::setRigidType(PhysicType type) {
    m_rigidType = type;
}

PhysicType ShapePhysic::getRigidType() const {
    return m_rigidType;
}

Matrix4 ShapePhysic::getTransform() const {
    if(!m_handle) {
        return Matrix4();
    }

    const Vec2f pos = priv::getVec2fFromBox2D(m_handle->GetPosition());

    if(pos.x != m_prevPos.x || pos.y != m_prevPos.y) {
        const float angle = -m_handle->GetAngle();
        const float c = std::cos(angle);
        const float s = std::sin(angle);

        const Vec2f scaleCos(m_scale.x * c, m_scale.y * c);
        const Vec2f scaleSin(m_scale.x * s, m_scale.y * s);

        const Vec2f origin = m_origin + m_size / 2;

        const Vec2f translation(
                -origin.x * scaleCos.x - origin.y * scaleSin.y + pos.x,
                 origin.x * scaleSin.x - origin.y * scaleCos.y + pos.y
        );

        m_matrix = Matrix4(
                { +scaleCos.x, scaleSin.y, 0.0, translation.x },
                { -scaleSin.x, scaleCos.y, 0.0, translation.y },
                {  0.0,        0.0,        1.0, 0.0 },
                {  0.0,        0.0,        0.0, 1.0 }
        );

        m_prevPos = pos;
    }

    return m_matrix;
}

void ShapePhysic::onPosChange(const Vec2f& prevPos) {
    if(m_handle) {
        m_handle->SetTransform(priv::getBox2dVec(m_pos), getRotationRad());
    }
}

void ShapePhysic::onOriginChange(const Vec2f& prevOrigin) {

}

void ShapePhysic::onRotationChange(float prevRotation) {
    if(m_handle) {
        m_handle->SetTransform(priv::getBox2dVec(m_pos), getRotationRad());
    }
}

} // namespace mg

