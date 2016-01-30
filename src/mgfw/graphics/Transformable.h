#pragma once

#include "../math/Vector2.h"
#include "../math/Matrix4.h"

namespace mg {

class Transformable {
public:
    Transformable();

    void setPos(const Vec2f& pos);
    void setPos(float x, float y);
    void setPos(float xy);
    Vec2f getPos() const;

    void setSize(const Vec2f& size);
    void setSize(float w, float h);
    void setSize(float wh);
    Vec2f getSize() const;

    void setScale(const Vec2f& scale);
    void setScale(float w, float h);
    void setScale(float wh);
    Vec2f getScale() const;

    void setOrigin(const Vec2f& origin);
    void setOrigin(float x, float y);
    void setOrigin(float xy);
    Vec2f getOrigin() const;

    void setRotation(float degrees);
    void setRotationRad(float radians);
    float getRotation() const;
    float getRotationRad() const;

    void move(const Vec2f& movement);
    void move(float x, float y);
    void move(float xy);

    void resize(const Vec2f& size);
    void resize(float w, float h);
    void resize(float wh);

    void rescale(const Vec2f& scale);
    void rescale(float w, float h);
    void rescale(float wh);

    void rotate(float degrees);
    void rotateRad(float radians);

    const Matrix4& getMatrix() const;

protected:
    Vec2f m_pos;
    Vec2f m_size;
    Vec2f m_scale;
    Vec2f m_origin;
    float m_rotation;   // Rotation is in degrees

    mutable Matrix4 m_matrix;
    mutable bool m_isUpdateMatrix;
};

} // namespace mg
