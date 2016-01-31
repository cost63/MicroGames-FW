#pragma once

#include <cmath>
#include <iostream>

namespace mg {

template <typename T>
struct Vector2 {
    union {
        T data[ 2 ];
        struct{ T x, y; };
        struct{ T w, h; };
        struct{ T s, t; };
    };

    /** Constructors */

    Vector2() : x( 0 ), y( 0 ) {}
    Vector2( T _x, T _y ) : x( _x ), y( _y ) {}
    Vector2( T _xy ) : x( _xy ), y( _xy ) {}
    Vector2( T _xy[ 2 ] ) : x( _xy[ 0 ] ), y( _xy[ 1 ] ) {}

    template <typename U>
    Vector2(const Vector2<U>& v) : x(v.x), y(v.y) {}

    /** Operators */

    T& operator[]( uint16_t index ) { return data[ index ]; }
    const T& operator[]( uint16_t index ) const { return data[ index ]; }

    template <typename U>
    bool operator==( const Vector2<U>& other ) const {
        return ( x == other.x ) && ( y == other.y );
    }
    template <typename U>
    bool operator!=( const Vector2<U>& other ) const {
        return !operator==( other );
    }

    template <typename U>
    Vector2<T> operator+( const Vector2<U>& other ) const {
        return Vector2<T>( x + other.x, y + other.y );
    }
    template <typename U>
    Vector2<T> operator+( U v ) const {
        return Vector2<T>( x + v, y + v );
    }
    template <typename U>
    Vector2<T>& operator+=( const Vector2<U>& other ) {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2<T> operator-() const {
        return Vector2<T>( - x, - y );
    }
    template <typename U>
    Vector2<T> operator-( const Vector2<U>& other ) const {
        return Vector2<T>( x - other.x, y - other.y );
    }
    template <typename U>
    Vector2<T>& operator-=( const Vector2<U>& other ) {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    Vector2<T> operator*( T scalar ) const {
        return Vector2<T>( x * scalar, y * scalar );
    }
    Vector2<T>& operator*=( T scalar ) {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    template <typename U>
    Vector2<T> operator*( const Vector2<U>& other ) const {
        return Vector2<T>( x * other.x, y * other.y );
    }

    template <typename U>
    Vector2<T> operator/(const Vector2<U>& other) const {
        return Vector2<T>(x / other.x, y / other.y);
    }
    Vector2<T> operator/( T scalar ) const {
        return Vector2<T>( x / scalar, y / scalar );
    }
    Vector2<T>& operator/=( T scalar ) {
        x /= scalar;
        y /= scalar;

        return *this;
    }
};

template <typename T, typename U>
float dot( const Vector2<T>& a, const Vector2<U>& b ) {
    return a.x * b.x + a.y * b.y;
}

template <typename T, typename U>
float cross( const Vector2<T>& a, const Vector2<U>& b ) {
    return a.x * b.y - a.y * b.x;
}

template <typename T>
float lenghtSquared( const Vector2<T>& a ) {
    return dot( a, a );
}

template <typename T>
float lenght( const Vector2<T>& a ) {
    return sqrt( lenghtSquared( a ) );
}

template <typename T>
Vector2<T> normalized( const Vector2<T>& a ) {
    return a * ( 1.0 / lenght( a ) );
}

template <typename T, typename U>
float angle( const Vector2<T>& a, const Vector2<U>& b ) {
    return std::atan2( b.y - a.y, b.x - a.x );
}

template <typename T>
std::ostream& operator<<( std::ostream& os, const Vector2<T>& v ) {
    return os << "Vector2( " << v.x << ", " << v.y << " )";
}

#define Vec2f Vector2<float>
#define Vec2i Vector2<int>
#define Vec2u Vector2<unsigned int>

} // namespace mg
