#pragma once

#include <iostream>

namespace mg
{

template <typename T> struct Vector2;
template <typename T> struct Vector4;

template <typename T>
struct Vector3
{
    union {
        T data[ 3 ];
        struct{ T x, y, z; };
        struct{ T w, h, d; };
        struct{ T r, g, b; };
        struct{ T s, t, p; };
    };

    /** Constructors */

    Vector3() : x( 0 ), y( 0 ), z( 0 ) {}
    Vector3( T _x, T _y, T _z ) : x( _x ), y( _y ), z( _z ) {}
    Vector3( T _xyz ) : x( _xyz ), y( _xyz ), z( _xyz ) {}
    Vector3( T _xyz[ 3 ] ) : x( _xyz[ 0 ] ), y( _xyz[ 1 ] ), z( _xyz[ 2 ] ) {}

    explicit Vector3( const Vector2<T>& other, T _z )
    : x( other.x )
    , y( other.y )
    , z( _z )
    {}

    explicit Vector3( const Vector4<T>& other )
    : x( other.x )
    , y( other.y )
    , z( other.z )
    {}

    /** Operators */

    T& operator[]( uint16_t index ) { return data[ index ]; }
    const T& operator[]( uint16_t index ) const { return data[ index ]; }

    template <typename V>
    bool operator==( const Vector3<V>& other ) const
    {
        return ( x == other.x ) && ( y == other.y ) && ( z == other.z );
    }
    template <typename V>
    bool operator!=( const Vector3<V>& other ) const
    {
        return !operator==( other );
    }

    template <typename V>
    Vector3<T> operator+( const Vector3<V>& other ) const
    {
        return Vector3<T>( x + other.x, y + other.y, z + other.z );
    }
    template <typename V>
    Vector3<T>& operator+=( const Vector3<V>& other ) const
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    template <typename V>
    Vector3<T> operator-( const Vector3<V>& other ) const
    {
        return Vector3<T>( x - other.x, y - other.y, z - other.z );
    }
    template <typename V>
    Vector3<T>& operator-=( const Vector3<V>& other ) const
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    Vector3<T> operator*( T scalar ) const
    {
        return Vector3<T>( x * scalar, y * scalar, z * scalar );
    }
    Vector3<T>& operator*=( T scalar ) const
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    template <typename V>
    Vector3<T> operator*( const Vector3<V>& other ) const
    {
        Vector3<T> result;

        for( uint8_t i = 0; i < 3; i++ ) {
            result[ i ] = data[ i ] * other[ i ];
        }

        return result;
    }

    Vector3<T> operator/( T scalar ) const
    {
        return Vector3<T>( x / scalar, y / scalar, z / scalar );
    }
    Vector3<T>& operator/=( T scalar ) const
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }
};

template <typename T>
Vector3<T> operator*( float scalar, const Vector3<T>& v )
{
    Vector3<T> result;

    for( uint8_t i = 0; i < 3; i++ )
        {
        result[ i ] = v[ i ] * scalar;
    }

    return result;
}

template <typename T, typename V>
float dot( const Vector3<T>& a, const Vector3<V>& b )
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T, typename V>
Vector3<float> cross( const Vector3<T>& a, const Vector3<V>& b )
{
    return Vector3<float>( a.y * b.z - b.y * a.z,  // x
                           a.z * b.x - b.z * a.x,  // y
                           a.x * b.y - b.x * a.y   // z
                         );
}

template <typename T>
float lenghtSquared( const Vector3<T>& a )
{
    return dot( a, a );
}

template <typename T>
float lenght( const Vector3<T>& a )
{
    return sqrt( lenghtSquared( a ) );
}

template <typename T>
Vector3<T> normalized( const Vector3<T>& v )
{
    return v * ( 1.0 / lenght( v ) );
}

template <typename T>
std::ostream& operator<<( std::ostream& os, const Vector3<T>& v )
{
    return os << "Vector3( " << v.x << ", " << v.y << ", " << v.z << " )";
}

#define Vec3f Vector3<float>
#define Vec3i Vector3<int>
#define Vec3u Vector3<unsigned int>

} // namespace mg
