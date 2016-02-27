#pragma once

#include "../graphics/Shape.h"
#include "../math/Box2D.h"

namespace mg {

class PhysicWorld;

enum PhysicType {
    Static,
    Dynamic,
    Kinematic
};

b2BodyType getB2Type(PhysicType type);

class ShapePhysic : public Shape {
public:
    ShapePhysic();

    void draw(Renderer& renderer, RenderStates states) const override;

    void setRigidType(PhysicType type);
    PhysicType getRigidType() const;

    virtual void addToWorld(PhysicWorld& world) = 0;

    void applyForceCenter(const Vec2f& force);
    void applyTorque(float torque);

    Matrix4 getTransform() const override;

protected:
    void onPosChange(const Vec2f& prevPos) override;
    void onOriginChange(const Vec2f& prevOrigin) override;
    void onRotationChange(float prevRotation) override;

protected:
    b2Body* m_handle;
    PhysicType m_rigidType;

    mutable Vec2f m_prevPos;
};

} // namespace mg
