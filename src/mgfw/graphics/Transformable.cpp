#include "Transformable.h"

#define PI 3.1415926535897

namespace mg
{

Transformable::Transformable()
{}

void Transformable::setPos(const Vec2f& pos)
{
    m_pos = pos;
}

void Transformable::setPos(float x, float y)
{
    setPos(Vec2f(x, y));
}

void Transformable::setPos(float xy)
{
    setPos(Vec2f(xy));
}

Vec2f Transformable::getPos() const
{
    return m_pos;
}


void Transformable::setSize(const Vec2f& size)
{
    m_size = size;
}

void Transformable::setSize(float w, float h)
{
    setSize(Vec2f(w, h));
}

void Transformable::setSize(float wh)
{
    setSize(Vec2f(wh));
}

Vec2f Transformable::getSize() const
{
    return m_size;
}


void Transformable::setScale(const Vec2f& scale)
{
    m_scale = scale;
}

void Transformable::setScale(float w, float h)
{
    setScale(Vec2f(w, h));
}

void Transformable::setScale(float wh)
{
    setScale(Vec2f(wh));
}

Vec2f Transformable::getScale() const
{
    return m_scale;
}


void Transformable::setOrigin(const Vec2f& origin)
{
    m_origin = origin;
}

void Transformable::setOrigin(float x, float y)
{
    setOrigin(Vec2f(x, y));
}

void Transformable::setOrigin(float xy)
{
    setOrigin(Vec2f(xy));
}

Vec2f Transformable::getOrigin() const
{
    return m_origin;
}


void Transformable::setRotation(float degrees)
{
    m_rotation = degrees;
}

void Transformable::setRotationRad(float radians)
{
    m_rotation = radians * (180 / PI);
}

float Transformable::getRotation() const
{
    return m_rotation;
}

float Transformable::getRotationRad() const
{
    return m_rotation * (PI / 180);
}


void Transformable::move(const Vec2f& movement)
{
    setPos(m_pos + movement);
}

void Transformable::move(float x, float y)
{
    move(Vec2f(x, y));
}

void Transformable::move(float xy)
{
    move(Vec2f(xy));
}


void Transformable::resize(const Vec2f& size)
{
    setSize(m_size + size);
}

void Transformable::resize(float w, float h)
{
    resize(Vec2f(w, h));
}

void Transformable::resize(float wh)
{
    resize(Vec2f(wh));
}


void Transformable::rescale(const Vec2f& scale)
{
    setScale(m_scale + scale);
}

void Transformable::rescale(float w, float h)
{
    rescale(Vec2f(w, h));
}

void Transformable::rescale(float wh)
{
    rescale(Vec2f(wh));
}


void Transformable::rotate(float degrees)
{
    m_rotation += degrees;
}

void Transformable::rotateRad(float radians)
{
    m_rotation += radians * (180 / PI);
}

} // namespace mg
