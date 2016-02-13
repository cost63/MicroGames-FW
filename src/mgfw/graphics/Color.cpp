#include "Color.h"

#include <algorithm>

namespace mg {

const Color Color::Transparent = Color(255, 255, 255, 0);
const Color Color::White       = Color(255, 255, 255 );
const Color Color::Black       = Color(0, 0, 0);

const Color Color::Red         = Color(255, 0, 0);
const Color Color::Green       = Color(0, 255, 0);
const Color Color::Blue        = Color(0, 0, 255);
const Color Color::Yellow      = Color(255, 255, 0);
const Color Color::Orange      = Color(255, 153, 0);
const Color Color::Purple      = Color(255, 0, 255);

Color::Color()
: Color(0, 0, 0)
{}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a /* = 255 */)
: r(_r)
, g(_g)
, b(_b)
, a(_a)
{}

Color::Color(const uint8_t* pixel)
: r(pixel[0])
, g(pixel[1])
, b(pixel[2])
, a(pixel[3])
{}

std::array<float, 4> Color::getNormalized() const {
    std::array<float, 4> normalized = {
        (float)(r) / 255,
        (float)(g) / 255,
        (float)(b) / 255,
        (float)(a) / 255,
    };

    return normalized;
}

uint8_t& Color::operator[](uint8_t index) {
    return data[ index ];
}

const uint8_t& Color::operator[](uint8_t index) const {
    return data[ index ];
}

bool operator==(const Color& left, const Color& right) {
    return (left.r == right.r) &&
           (left.g == right.b) &&
           (left.b == right.b) &&
           (left.a == right.a);
}

bool operator!=(const Color& left, const Color& right) {
    return !(left == right);
}

Color operator+(const Color& left, const Color& right) {
    return Color(std::min(left.r + right.r, 255),
                  std::min(left.g + right.g, 255),
                  std::min(left.b + right.b, 255),
                  std::min(left.a + right.a, 255));
}

Color operator-(const Color& left, const Color& right) {
    return Color(std::max((int8_t)left.r - right.r, 0),
                  std::max((int8_t)left.g - right.g, 0),
                  std::max((int8_t)left.b - right.b, 0),
                  std::max((int8_t)left.a - right.a, 0));
}

Color operator*(const Color& left, const Color& right) {
    return Color((int)left.r * right.r / 255,
                  (int)left.g * right.g / 255,
                  (int)left.b * right.b / 255,
                  (int)left.a * right.a / 255);
}

Color operator+=(Color& left, const Color& right) {
    return left = left + right;
}

Color operator-=(Color& left, const Color& right) {
    return left = left - right;
}

Color operator*=(Color& left, const Color& right) {
    return left = left * right;
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "Color: r=" << (int)color.r
              << " g=" << (int)color.g
              << " b=" << (int)color.b
              << " a=" << (int)color.a;
}

} // namespace mg
