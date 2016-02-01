#pragma once

#include "../graphics/Shape.h"

namespace mg {

class CircleShape : public Shape {
public:
    CircleShape();

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
