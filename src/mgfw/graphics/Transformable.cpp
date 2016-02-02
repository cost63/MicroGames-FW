#include "Transformable.h"

#define PI 3.1415926535897

namespace mg {

Transformable::Transformable()
: m_scale(Vec2f(1.0, 1.0))
, m_rotation(0.0)
, m_isUpdateMatrix(true)
{}

void Transformable::setPos(const Vec2f& pos) {
    const Vec2f prev = m_pos;

    m_pos = pos;

    m_isUpdateMatrix = true;

    onPosChange(prev);
}

void Transformable::setPos(float x, float y) {
    setPos(Vec2f(x, y));
}

void Transformable::setPos(float xy) {
    setPos(Vec2f(xy));
}

Vec2f Transformable::getPos() const {
    return m_pos;
}


void Transformable::setSize(const Vec2f& size) {
    const Vec2f prev = m_size;

    m_size = size;

    m_isUpdateMatrix = true;

    onSizeChange(prev);
}

void Transformable::setSize(float w, float h) {
    setSize(Vec2f(w, h));
}

void Transformable::setSize(float wh) {
    setSize(Vec2f(wh));
}

Vec2f Transformable::getSize() const {
    return m_size;
}

void Transformable::setCenter(const Vec2f& center) {
    setPos(center - m_size / 2);
}

void Transformable::setCenter(float x, float y) {
    setCenter(Vec2f(x, y));
}

void Transformable::setCenter(float xy) {
    setCenter(Vec2f(xy));
}

Vec2f Transformable::getCenter() const {
    return m_pos + m_size / 2;
}

void Transformable::setBox(const fRect& box) {
    setPos(box.pos());
    setSize(box.size());
}

void Transformable::setBox(const Vec2f& pos, const Vec2f& size) {
    setPos(pos);
    setSize(size);
}

void Transformable::setBox(float x, float y, float w, float h) {
    setPos(x, y);
    setSize(x, y);
}

void Transformable::setBox(float xy, float wh) {
    setPos(xy);
    setSize(wh);
}

void Transformable::setBox(float xywh) {
    setPos(xywh);
    setSize(xywh);
}

fRect Transformable::getBox() const {
    return fRect(m_pos, m_size);
}

void Transformable::setScale(const Vec2f& scale) {
    const Vec2f prev = m_scale;

    m_scale = scale;

    m_isUpdateMatrix = true;

    onScaleChange(prev);
}

void Transformable::setScale(float w, float h) {
    setScale(Vec2f(w, h));
}

void Transformable::setScale(float wh) {
    setScale(Vec2f(wh));
}

Vec2f Transformable::getScale() const {
    return m_scale;
}

void Transformable::setOrigin(const Vec2f& origin) {
    const Vec2f prev = m_origin;

    m_origin = origin;

    m_isUpdateMatrix = true;

    onOriginChange(prev);
}

void Transformable::setOrigin(float x, float y) {
    setOrigin(Vec2f(x, y));
}

void Transformable::setOrigin(float xy) {
    setOrigin(Vec2f(xy));
}

Vec2f Transformable::getOrigin() const {
    return m_origin;
}


void Transformable::setRotation(float degrees) {
    const float prev = m_rotation;

    m_rotation = degrees;

    m_isUpdateMatrix = true;

    onRotationChange(prev);
}

void Transformable::setRotationRad(float radians) {
    const float prev = m_rotation;

    m_rotation = radians * (180 / PI);

    m_isUpdateMatrix = true;

    onRotationChange(prev);
}

float Transformable::getRotation() const {
    return m_rotation;
}

float Transformable::getRotationRad() const {
    return m_rotation * (PI / 180);
}


void Transformable::move(const Vec2f& movement) {
    setPos(m_pos + movement);
}

void Transformable::move(float x, float y) {
    move(Vec2f(x, y));
}

void Transformable::move(float xy) {
    move(Vec2f(xy));
}


void Transformable::resize(const Vec2f& size) {
    setSize(m_size + size);
}

void Transformable::resize(float w, float h) {
    resize(Vec2f(w, h));
}

void Transformable::resize(float wh) {
    resize(Vec2f(wh));
}


void Transformable::rescale(const Vec2f& scale) {
    setScale(m_scale + scale);
}

void Transformable::rescale(float w, float h) {
    rescale(Vec2f(w, h));
}

void Transformable::rescale(float wh) {
    rescale(Vec2f(wh));
}


void Transformable::rotate(float degrees) {
    setRotation(m_rotation + degrees);
}

void Transformable::rotateRad(float radians) {
    setRotationRad(m_rotation + radians * (180 / PI));
}

const Matrix4& Transformable::getMatrix() const {
    if(m_isUpdateMatrix) {
        m_matrix = Matrix4();

        // Position
        m_matrix.translate(m_pos - m_origin);

        // Rotation
        m_matrix.translate(m_origin);
        m_matrix.rotate(m_rotation * (PI / 180));
        m_matrix.translate(-m_origin);

        // Size
        m_matrix.scale(m_scale * m_size);

        m_isUpdateMatrix = false;
    }

    return m_matrix;
}

} // namespace mg
