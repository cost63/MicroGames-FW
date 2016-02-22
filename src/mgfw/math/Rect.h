#pragma once

#include "../math/Vector2.h"
#include "../math/Vector4.h"

namespace mg {

template <typename T>
struct Rect {
    union {
        T data[4];
        struct{ T x, y, w, h; };
    };

    /* Constructors */

    Rect() : x(0), y(0), w(0), h(0) {}
    Rect(T _x, T _y, T _w, T _h) : x(_x), y(_y), w(_w), h(_h) {}
    Rect(T _xy, T _wh) : x(_xy), y(_xy), w(_wh), h(_wh) {}
    Rect(T _xywh) : x(_xywh), y(_xywh), w(_xywh), h(_xywh) {}

    template <typename U, typename V>
    Rect(const Vector2<U>& xy, const Vector2<V>& wh )
    : x(xy.x), y(xy.y), w(wh.w) , h(wh.h)
    {}

    template <typename U>
    Rect(const Vector2<U>& xy, T _w, T _h )
    : x(xy.x), y(xy.y), w(_w), h(_h)
    {}

    template <typename U>
    Rect(T _x, T _y, const Vector2<U>& wh)
    : x(_x), y(_y), w(wh.w), h(wh.h)
    {}

    template <typename U>
    Rect(const Vector4<U>& xywh)
    : x(xywh.x), y(xywh.y), w(xywh.z), h(xywh.w)
    {}

    /* Operators */

    T& operator[](uint8_t index) { return data[ index ]; }
    const T& operator[](uint8_t index) const { return data[ index ]; }

    template <typename U>
    bool operator==(const Rect<U>& other) const {
        return (x == other.x) && (y == other.y) && (w == other.w) && (h == other.h);
    }

    template <typename U>
    bool operator!=(const Rect<U>& other) const {
        return !operator==(other);
    }

    template <typename U>
    Rect<T> operator+(const Rect<U>& other) const {
        return Rect<T>(x + other.x, y + other.y, w + other.w, h + other.h);
    }
    template <typename U>
    Rect<T>& operator+=(const Rect<U>& other) {
        return *this = (*this + other);
    }

    template <typename U>
    Rect<T> operator-(const Rect<U>& other) const {
        return Rect<T>(x - other.x, y - other.y, w - other.w, h - other.h);
    }
    template <typename U>
    Rect<T>& operator-=(const Rect<U>& other) {
        return *this = (*this - other);
    }

    template <typename U>
    Rect<T> operator*(const Rect<U>& other) const {
        return Rect<T>(x * other.x, y * other.y, w * other.w, h * other.h);
    }
    template <typename U>
    Rect<T> operator*(U scalar) const {
        return Rect<T>(x * scalar, y * scalar, w * scalar, h * scalar);
    }
    template <typename U>
    Rect<T>& operator*=(const Rect<U>& other) {
        return *this = (*this * other);
    }

    template <typename U>
    Rect<T> operator/(const Rect<U>& other) const {
        return Rect<T>(x / other.x, y / other.y, w / other.w, h / other.h);
    }
    template <typename U>
    Rect<T> operator/(U scalar) const {
        return Rect<T>(x / scalar, y / scalar, w / scalar, h / scalar);
    }
    template <typename U>
    Rect<T>& operator/=(const Rect<U>& other) {
        return *this = (*this / other);
    }

    /* Methods */
    Vector2<T> pos() const {
        return Vector2<T>(x, y);
    }
    Vector2<T> size() const {
        return Vector2<T>(w, h);
    }
    T right() const {
        return x + w;
    }
    T bottom() const {
        return y + h;
    }

    template <typename U>
    bool contains(const Vector2<U>& point) const {
        return !(point.x < x ||
                 point.x > right() ||
                 point.y < y ||
                 point.y > bottom());
    }

    template <typename U>
    bool contains(const Rect<U>& other) const {
        return !(other.x < x ||
                 other.right() > right() ||
                 other.y < y ||
                 other.bottom() > bottom());
    }

    template <typename U>
    bool collides(const Rect<U>& other) const {
        return !(other.x > right() ||
                 other.right() < x ||
                 other.y > bottom() ||
                 other.bottom() < y);
    }
};

template <typename T>
std::ostream& operator<<( std::ostream& os, const Rect<T>& r ) {
    return os << "Rect( " << r.x << ", " << r.y << ", " << r.w << ", " << r.h << " )";
}

#define iRect Rect<int>
#define fRect Rect<float>
#define uRect Rect<uint32_t>

} // namespace mg
