#pragma once

#ifdef MG_GCC
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif // MG_GCC

#include <array>
#include <iostream>

namespace mg {

struct Color {
    union {
        uint8_t data[4];
        struct{ uint8_t r, g, b, a; };
    };

    Color();
    Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255);

    uint8_t& operator[](uint8_t index);
    const uint8_t& operator[](uint8_t index) const;

    std::array<float, 4> getNormalized() const;

    static const Color Transparent;
    static const Color White;
    static const Color Black;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Orange;
    static const Color Purple;
};

bool operator==(const Color& left, const Color& right);
bool operator!=(const Color& left, const Color& right);
Color operator+(const Color& left, const Color& right);
Color operator-(const Color& left, const Color& right);
Color operator*(const Color& left, const Color& right);
Color operator+=(Color& left, const Color& right);
Color operator-=(Color& left, const Color& right);
Color operator*=(Color& left, const Color& right);
std::ostream& operator<<(std::ostream& os, const Color& color);

} // namespace mg
