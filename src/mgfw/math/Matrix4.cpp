#include "Matrix4.h"

#include <cmath>

namespace mg {

Vec4f& Matrix4::operator[](uint8_t index) {
    return data[index];
}

const Vec4f& Matrix4::operator[](uint8_t index) const {
    return data[index];
}

bool Matrix4::operator==(const Matrix4& other) const {
    for(uint8_t i = 0; i < 4; i++) {
        if(data[i] != other[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const {
    return !operator==(other);
}


Matrix4 Matrix4::operator+(const Matrix4& other) const {
    Matrix4 m;

    for(uint8_t i = 0; i < 4; i++) {
        m[i] = data[i] + other[i];
    }

    return m;
}
Matrix4& Matrix4::operator+=(const Matrix4& other) {
    return (*this = (*this) + other);
}

Matrix4 Matrix4::operator-(const Matrix4& other) const {
    Matrix4 m;

    for(uint8_t i = 0; i < 4; i++) {
        m[i] = data[i] - other[i];
    }

    return m;
}
Matrix4& Matrix4::operator-=(const Matrix4& other) {
    return (*this = (*this) - other);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;

    for(int aRow = 0; aRow < 4; aRow++) {
        for(int bColumn = 0; bColumn < 4; bColumn++) {
            float sum = 0;

            for(int i = 0; i < 4; i++) {
                sum += data[aRow][i] * other[i][bColumn];
            }

            result[aRow][bColumn] = sum;
        }
    }

    return result;
}
Matrix4& Matrix4::operator*=(const Matrix4& other) {
    return (*this = (*this) * other);
}



Matrix4 Matrix4::operator/(float scalar) const {
    Matrix4 m;

    for(uint8_t i = 0; i < 4; i++) {
        m[i] = data[i] / scalar;
    }

    return m;
}

Matrix4 Matrix4::transpose(const Matrix4& m) {
    Matrix4 result;

    for(uint8_t i = 0; i < 4; i++) {
        for(uint8_t j = 0; j < 4; j++) {
            result[i][j] = m[j][i];
        }
    }

    return result;
}

void Matrix4::rotate(float radians) {
    Matrix4 result;

    float c = std::cos(radians);
    float s = std::sin(radians);

    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;

    (*this) *= result;
}

void Matrix4::translate(const Vec2f& translation) {
    Matrix4 result;

    result[0][3] = translation.x;
    result[1][3] = translation.y;

    (*this) *= result;
}

void Matrix4::scale(const Vec2f& scaleVector) {
    Matrix4 result;

    result[0][0] = scaleVector.x;
    result[1][1] = scaleVector.y;

    (*this) *= result;
}

Vec4f operator*(const Matrix4& m, const Vec4f& v) {
    Vec4f result;

    for(uint8_t i = 0; i < 4; i++) {
        for(uint8_t j = 0; j < 4; j++) {
            result[i] += m[i][j] * v[j];
        }
    }

    return result;
}

Matrix4 operator*(const Matrix4& m, float scalar) {
    Matrix4 result;

    for(uint8_t i = 0; i < 4; i++) {
        result[i] = m[i] * scalar;
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m) {
    os << "Matrix4: " << std::endl;

    for(uint8_t i = 0; i < 4; i++) {
        os << "  ";

        for(uint8_t j = 0; j < 4; j++) {
            os << m[i][j] << ", ";
        }

        os << std::endl;
    }

    return os;
}

Matrix4 ortho(float left, float right, float bottom, float top) {
    Matrix4 result;

    result[0][0] = 2.0 / (right - left);
    result[1][1] = 2.0 / (top - bottom);
    result[0][3] = - (right + left) / (right - left);
    result[1][3] = - (top + bottom) / (top - bottom);

    return result;
}

Matrix4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
    Matrix4 result;

    result[0][0] = 2.0 / (right - left);
    result[1][1] = 2.0 / (top - bottom);
    result[2][2] = 2.0 / (zFar - zNear);
    result[0][3] = -(right + left) / (right - left);
    result[1][3] = -(top + bottom) / (top - bottom);
    result[2][3] = -(zFar + zNear) / (zFar - zNear);

    return result;
}

} // namespace mg
