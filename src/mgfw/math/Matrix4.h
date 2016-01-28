#pragma once

#include <array>
#include <iostream>

#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"

namespace mg {

struct Matrix4 {
    Vec4f data[4];

    Matrix4()
    : data{
            { 1, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 },
          }
    {}

    Matrix4(float x)
    : data{
            { x, 0, 0, 0 },
            { 0, x, 0, 0 },
            { 0, 0, x, 0 },
            { 0, 0, 0, x },
          }
    {}

    Matrix4(const Vec4f& v0, const Vec4f& v1, const Vec4f& v2, const Vec4f& v3)
    : data{ v0, v1, v2, v3 }
    {}

    Vec4f& operator[](uint8_t index);
    const Vec4f& operator[](uint8_t index) const;

    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;

    Matrix4 operator+(const Matrix4& other) const;
    Matrix4& operator+=(const Matrix4& other);

    Matrix4 operator-(const Matrix4& other) const;
    Matrix4& operator-=(const Matrix4& other);

    Matrix4 operator*(const Matrix4& other) const;
    Matrix4& operator*=(const Matrix4& other);

    Matrix4 operator/(float scalar) const;

    /** Methods */

    void translate(const Vec2f& translation);
    void rotate(float radians);
    void scale(const Vec2f& scaleVector);

    Matrix4 transpose(const Matrix4& m);
};

Vec4f operator*(const Matrix4& m, const Vec4f& v);
Matrix4 operator*(const Matrix4& m, float scalar);

std::ostream& operator<<(std::ostream& os, const Matrix4& m);

Matrix4 ortho(float left, float right, float bottom, float top);
Matrix4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

} // namespace mg
