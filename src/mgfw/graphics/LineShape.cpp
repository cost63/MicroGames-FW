#include "LineShape.h"

#include <cmath>

namespace mg {

// TODO(All) Move these functions to separate file
float length(const Vec2f& first, const Vec2f& second) {
    return std::sqrt(std::pow(first.y - second.y, 2) + std::pow(first.x - second.x, 2));;
}

float angleByVectors(const Vec2f& first, const Vec2f& second ) {
    return std::atan2(second.y - first.y, second.x - first.x);
}

/* Operators */

Vec2f& LineShape::operator[](uint32_t i) {
    return m_sagments[i];
}

const Vec2f& LineShape::operator[](uint32_t i) const {
    return m_sagments[i];
}

/* Methods */

LineShape::LineShape()
: m_type(LineShape::Separate)
{
    m_vertices.type = PrimitiveType::LineStrip;

    m_vertices.resize(4);

    const Vec2f p1 = {50, 40};
    const Vec2f p2 = {300, 300};

    const Vec2f& initPoint = p1;
    const float width = 14.0;
    const float radius = width / 2;

    float sagmentAngle = angleByVectors(p1, p2);
    float s = std::sin(sagmentAngle);
    float c = std::cos(sagmentAngle);

    m_vertices[0].pos.x = initPoint.x - radius * s;
    m_vertices[0].pos.y = initPoint.y + radius * c;

    m_vertices[1].pos.x = initPoint.x + radius * s;
    m_vertices[1].pos.y = initPoint.y - radius * c;

    m_vertices[2].pos.x = p2.x + radius * s;
    m_vertices[2].pos.y = p2.y - radius * c;

    m_vertices[3].pos.x = p2.x - radius * s;
    m_vertices[3].pos.y = p2.y + radius * c;
}

void LineShape::updateVertices() {
    if(getSagmentCount() < 2) {
        return;
    }

    if(m_type == LineShape::Separate) {
        m_vertices.resize(getSagmentCount() * 4);

    }
    else {
        m_vertices.resize(getSagmentCount() * 2 + 2);

        const Vec2f& initPoint = m_sagments[0];
        const float width = 6.0;
        const float radius = width / 2;

        float sagmentAngle = angleByVectors(m_sagments[0], m_sagments[1]);
        float s = std::sin(sagmentAngle);
        float c = std::cos(sagmentAngle);

        m_vertices[0].pos.x = initPoint.x + radius * c;
        m_vertices[0].pos.y = initPoint.y + radius * s;

        m_vertices[1].pos.x = initPoint.x - radius * c;
        m_vertices[1].pos.y = initPoint.y - radius * s;
    }
}

void LineShape::setType(LineShape::Type type) {
    m_type = type;

    if(m_type == LineShape::Separate) {
        m_vertices.type = PrimitiveType::Lines;
    }
    else {
        m_vertices.type = PrimitiveType::LineStrip;
    }
}

void LineShape::setSagmentCount(uint32_t count) {
    m_sagments.resize(count);

    updateVertices();
}

uint32_t LineShape::getSagmentCount() const {
    return m_sagments.size();
}
} // namespace mg
