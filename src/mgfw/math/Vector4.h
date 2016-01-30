#pragma once

#include <iostream>

namespace mg {

template <typename T> struct Vector2;
template <typename T> struct Vector3;

template <typename T>
struct Vector4 {
    union {
        T data[ 4 ];
        struct{ T x, y, z, w; };
        struct{ T r, g, b, a; };
        struct{ T s, t, p, q; };
    };

    /** Constructors */

    Vector4() : x( 0 ), y( 0 ), z( 0 ), w( 0 ) {}
    Vector4( T _x, T _y, T _z, T _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}
    Vector4( T _xyzw ) : x( _xyzw ), y( _xyzw ), z( _xyzw ), w( _xyzw ) {}
    Vector4( T _xyzw[ 3 ] ) : x( _xyzw[ 0 ] ), y( _xyzw[ 1 ] ), z( _xyzw[ 2 ] ), w( _xyzw[ 3 ] ) {}

    template <typename U>
    Vector4(const Vector4<U>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    explicit Vector4( const Vector2<T>& other, T _z, T _w )
    : x( other.x )
    , y( other.y )
    , z( _z )
    , w( _w )
    {}

    explicit Vector4( const Vector2<T>& xy, const Vector2<T>& zw )
    : x( xy.x )
    , y( xy.y )
    , z( zw.x )
    , w( zw.y )
    {}

    explicit Vector4( const Vector3<T>& other, T _w )
    : x( other.x )
    , y( other.y )
    , z( other.z )
    , w( _w )
    {}

    /** Operators */

    T& operator[]( uint16_t index ) { return data[ index ]; }
    const T& operator[]( uint16_t index ) const { return data[ index ]; }

    template <typename U>
    bool operator==( const Vector4<U>& other ) const {
        return ( x == other.x ) && ( y == other.y ) && ( z == other.z ) && ( w == other.w );
    }
    template <typename U>
    bool operator!=( const Vector4<U>& other ) const {
        return !operator==( other );
    }

    template <typename U>
    Vector4<T> operator+( const Vector4<U>& other ) const {
        return Vector4<T>( x + other.x, y + other.y, z + other.z, w + other.w );
    }
    template <typename U>
    Vector4<T>& operator+=( const Vector4<U>& other ) const {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    template <typename U>
    Vector4<T> operator-( const Vector4<U>& other ) const {
        return Vector4<T>( x - other.x, y - other.y, z - other.z, w - other.w );
    }
    template <typename U>
    Vector4<T>& operator-=( const Vector4<U>& other ) const {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    Vector4<T> operator*( T scalar ) const {
        return Vector4<T>( x * scalar, y * scalar, z * scalar, w * scalar );
    }
    Vector4<T>& operator*=( T scalar ) const {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    template <typename U>
    Vector4<T> operator*( const Vector4<U>& other ) const {
        return Vector3<T>( x * other.x, y * other.y, z * other.z, w * other.w );
    }

    Vector4<T> operator/( T scalar ) const {
        return Vector4<T>( x / scalar, y / scalar, z / scalar, w / scalar );
    }
    Vector4<T>& operator/=( T scalar ) const {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }
};

template <typename T, typename U>
float dot( const Vector4<T>& a, const Vector4<U>& b ) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T, typename U>
float lenghtSquared( const Vector4<T>& a ) {
    return dot( a, a );
}

template <typename T, typename U>
float lenght( const Vector4<T>& a ) {
    return sqrtf( lenghtSquared( a ) );
}

template <typename T>
Vector4<T> normalized( const Vector4<T>& a ) {
    return a * ( 1.0 / lenght( a ) );
}

template <typename T>
std::ostream& operator<<( std::ostream& os, const Vector4<T>& v ) {
    return os << "Vector2( " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " )";
}

#define Vec4f Vector4<float>
#define Vec4i Vector4<int>
#define Vec4u Vector4<unsigned int>

} // namespace mg
