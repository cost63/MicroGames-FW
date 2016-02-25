#pragma once

#include "../math/Box2D.h"
#include "../graphics/RectShape.h"

namespace mg {

class PhysicRect : public RectShape {
public:
    PhysicRect();
    ~PhysicRect();

    void addToWorld(b2World& world);

    void applyForceCenter(const Vec2f& force);

    Matrix4 getTransform() const override;

private:
    void onPosChange(const Vec2f& prevPos) override;
    void onSizeChange(const Vec2f& prevSize) override;
    void onOriginChange(const Vec2f& prevOrigin) override;
    void onRotationChange(float prevRotation) override;

private:
    b2Body* m_handle;

    mutable Vec2f m_prevPos;
};

} // namespace mg
