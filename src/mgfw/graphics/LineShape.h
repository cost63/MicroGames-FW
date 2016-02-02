#pragma once

#include "../graphics/Shape.h"

namespace mg {

class LineShape : public Shape {
public:
    enum Type {
        Separate,
        Strip
    };

public:
    Vec2f& operator[](uint32_t i);
    const Vec2f& operator[](uint32_t i) const;

public:
    LineShape();

    void updateVertices();

    void setType(LineShape::Type type);
    LineShape::Type getType() const;

    void setSagmentCount(uint32_t count);
    uint32_t getSagmentCount() const;

private:
    LineShape::Type m_type;

    std::vector<Vec2f> m_sagments;

};

} // namespace mg
