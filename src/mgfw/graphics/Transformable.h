#pragma once

#include "../math/Vector2.h"
#include "../math/Matrix4.h"
#include "../math/Rect.h"

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

    void setCenter(const Vec2f& center);
    void setCenter(float x, float y);
    void setCenter(float xy);
    Vec2f getCenter() const;

    void setBox(const fRect& box);
    void setBox(const Vec2f& pos, const Vec2f& size);
    void setBox(float x, float y, float w, float h);
    void setBox(float xy, float wh);
    void setBox(float xywh);
    fRect getBox() const;

    void setScale(const Vec2f& scale);
    void setScale(float w, float h);
    void setScale(float wh);
    Vec2f getScale() const;

    void setOrigin(const Vec2f& origin);
    void setOrigin(float x, float y);
    void setOrigin(float xy);
    Vec2f getOrigin() const;

    // Sets origin to be at the center of the size
    void centerOrigin();

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

    virtual Matrix4 getTransform() const;

    const Matrix4& getMatrix() const;

protected:
    virtual void onPosChange(const Vec2f& prevPos) {}
    virtual void onSizeChange(const Vec2f& prevSize) {}
    virtual void onScaleChange(const Vec2f& prevScale) {}
    virtual void onOriginChange(const Vec2f& prevOrigin) {}
    virtual void onRotationChange(float prevRotation) {}

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
