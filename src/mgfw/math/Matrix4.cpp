#include "Matrix4.hpp"

#include <cmath>

namespace mg {

Vec4f& Matrix4::operator[](uint8_t index)
{
    return data[index];
}

const Vec4f& Matrix4::operator[](uint8_t index) const
{
    return data[index];
}

bool Matrix4::operator==(const Matrix4& other) const
{
    for(uint8_t i = 0; i < 4; i++) {
        if(data[i] != other[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
    return !operator==(other);
}


Matrix4 Matrix4::operator+(const Matrix4& other) const
{
    Matrix4 m;

    for(uint8_t i = 0; i < 4; i++) {
        m[i] = data[i] + other[i];
    }

    return m;
}
Matrix4& Matrix4::operator+=(const Matrix4& other)
{
    return (*this = (*this) + other);
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
    Matrix4 m;

    for(uint8_t i = 0; i < 4; i++) {
        m[i] = data[i] - other[i];
    }

    return m;
}
Matrix4& Matrix4::operator-=(const Matrix4& other)
{
    return (*this = (*this) - other);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
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
Matrix4& Matrix4::operator*=(const Matrix4& other)
{
    return (*this = (*this) * other);
}



Matrix4 Matrix4::operator/(float scalar) const
{
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

float determinant(const Matrix4& m) {
    // Note: These calculation are taken from internet
    const float coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    const float coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    const float coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    const float coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    const float coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    const float coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
    const float coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    const float coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    const float coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    const float coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    const float coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    const float coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
    const float coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    const float coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    const float coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
    const float coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    const float coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    const float coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    const Vec4f fac0(coef00, coef00, coef02, coef03);
    const Vec4f fac1(coef04, coef04, coef06, coef07);
    const Vec4f fac2(coef08, coef08, coef10, coef11);
    const Vec4f fac3(coef12, coef12, coef14, coef15);
    const Vec4f fac4(coef16, coef16, coef18, coef19);
    const Vec4f fac5(coef20, coef20, coef22, coef23);

    const Vec4f vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
    const Vec4f vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
    const Vec4f vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
    const Vec4f vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

    const Vec4f inv0 = vec1 * fac0 - vec2 * fac1 + vec3 * fac2;
    const Vec4f inv1 = vec0 * fac0 - vec2 * fac3 + vec3 * fac4;
    const Vec4f inv2 = vec0 * fac1 - vec1 * fac3 + vec3 * fac5;
    const Vec4f inv3 = vec0 * fac2 - vec1 * fac4 + vec2 * fac5;

    const Vec4f signA(+1, -1, +1, -1);
    const Vec4f signB(-1, +1, -1, +1);
    const Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

    const Vec4f row0(
                      inverse[0][0],
                      inverse[1][0],
                      inverse[2][0],
                      inverse[3][0]
                   );

    const Vec4f dot0(m[0] * row0);
    return dot0.x + dot0.y + dot0.z + dot0.w;
}


Matrix4 inverse(const Matrix4& m) {
    // Note: These calculation are taken from internet
	const float coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	const float coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	const float coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
	const float coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	const float coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	const float coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
	const float coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	const float coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	const float coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
	const float coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	const float coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	const float coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
	const float coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	const float coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	const float coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
	const float coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	const float coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	const float coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

	const Vec4f fac0(coef00, coef00, coef02, coef03);
	const Vec4f fac1(coef04, coef04, coef06, coef07);
	const Vec4f fac2(coef08, coef08, coef10, coef11);
	const Vec4f fac3(coef12, coef12, coef14, coef15);
	const Vec4f fac4(coef16, coef16, coef18, coef19);
	const Vec4f fac5(coef20, coef20, coef22, coef23);

	const Vec4f vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
	const Vec4f vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
	const Vec4f vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
	const Vec4f vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

	const Vec4f inv0 = vec1 * fac0 - vec2 * fac1 + vec3 * fac2;
	const Vec4f inv1 = vec0 * fac0 - vec2 * fac3 + vec3 * fac4;
	const Vec4f inv2 = vec0 * fac1 - vec1 * fac3 + vec3 * fac5;
	const Vec4f inv3 = vec0 * fac2 - vec1 * fac4 + vec2 * fac5;

	const Vec4f signA = { +1, -1, +1, -1 };
	const Vec4f signB = { -1, +1, -1, +1 };
	const Matrix4 inverse = {inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB};

	const Vec4f row0(
                      inverse[0][0],
                      inverse[1][0],
                      inverse[2][0],
                      inverse[3][0]
                   );

	const Vec4f dot0 = m[0] * row0;
	const float dot1 = (dot0[0] + dot0[1]) + (dot0[2] + dot0[3]);

	const float oneOverDeterminant = 1.0f / dot1;

	return inverse * oneOverDeterminant;
}

Matrix4 hadamardProduct(const Matrix4& a, const Matrix4& b) {
    Matrix4 result;

    for(uint8_t i = 0; i < 4; i++) {
        result[i] = a[i] * b[i];
    }

    return result;
}

Matrix4 translate(const Vec3f& v) {
    Matrix4 result;
    result[3] = Vec4f(v, 1.0);
    return result;
}

Matrix4 rotate(float rAngle, const Vec3f& v) {
    const float c = std::cos(rAngle);
    const float s = std::sin(rAngle);

    const Vec3f axis(normalized(v));
    const Vec3f t = (1.0 - c) * axis;

    Matrix4 rot;

    rot[0][0] = c + t[0] * axis[0];
    rot[0][1] = 0 + t[0] * axis[1] + s * axis[2];
    rot[0][2] = 0 + t[0] * axis[2] - s * axis[1];
    rot[0][3] = 0;

    rot[1][0] = 0 + t[1] * axis[0] - s * axis[2];
    rot[1][1] = c + t[1] * axis[1];
    rot[1][2] = 0 + t[1] * axis[2] + s * axis[0];
    rot[1][3] = 0;

    rot[2][0] = 0 + t[2] * axis[0] + s * axis[1];
    rot[2][1] = 0 + t[2] * axis[1] - s * axis[0];
    rot[2][2] = c + t[2] * axis[2];
    rot[2][3] = 0;

    return rot;
}

Matrix4 scale(const Vec3f& v) {
    return Matrix4(
                    { v.x, 0, 0, 0 },
                    { 0, v.y, 0, 0 },
                    { 0, 0, v.z, 0 },
                    { 0, 0, 0, 1 }
                 );
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

Matrix4 translate(const Matrix4& m, const Vec2f& translation) {
    Matrix4 result;

    result[0][3] = translation.x;
    result[1][3] = translation.y;

    return m * result;
}

Matrix4 rotate(const Matrix4& m, float radians) {
    Matrix4 result;

    float c = std::cos(radians);
    float s = std::sin(radians);

    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;

    return m * result;
}

Matrix4 scale(const Matrix4& m, const Vec2f& scaleVector) {
    Matrix4 result;

    result[0][0] = scaleVector.x;
    result[1][1] = scaleVector.y;

    return m * result;
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

Matrix4 test(const Matrix4& a, const Matrix4& b) {
    Matrix4 result;

    for(uint8_t aRow = 0; aRow < 4; aRow++) {
        for(uint8_t bColumn = 0; bColumn < 4; bColumn++) {
            float sum = 0;

            for(uint8_t i = 0; i < 4; i++) {
                sum += a[aRow][i] * b[i][bColumn];
            }

            result[aRow][bColumn] = sum;
        }
    }

    return result;
}

} // namespace mg
