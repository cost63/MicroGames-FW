#pragma once

#include "../math/ShapePhysic.h"

namespace mg {

class CircleShapePhysic : public ShapePhysic {
public:
    CircleShapePhysic();

    void addToWorld(PhysicWorld& world) override;

    void setRadius(float radius);
    float getRadius() const;

    void setSagmentCount(uint32_t count);
    uint32_t getSagmentCount() const;

private:
    void updateVertices();

private:
    float m_radius;
    uint32_t m_sagmentCount;

};

} // namespace mg
