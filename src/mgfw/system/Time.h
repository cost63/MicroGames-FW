#pragma once

#ifdef MG_GCC
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif // MG_GCC

namespace mg {

class Time {
public:
    Time();
    Time(uint32_t ms);

    /* Operators */

    bool operator==(Time other) const;
    bool operator!=(Time other) const;

    bool operator>(Time other) const;
    bool operator>=(Time other) const;
    bool operator<(Time other) const;
    bool operator<=(Time other) const;

    Time operator+(Time other) const;
    Time& operator+=(Time other);

    Time operator-(Time other) const;
    Time& operator-=(Time other);

    Time operator*(Time other) const;
    Time& operator*=(Time other);

    Time operator/(Time other) const;
    Time& operator/=(Time other);

    /* Methods */

    float asSeconds() const;
    uint32_t asMilliseconds() const;
    uint64_t asMicroseconds() const;

    /* Static methods */

    static Time Seconds(float s);
    static Time Milliseconds(uint32_t ms);
    static Time Microseconds(uint64_t ms);

private:
    uint32_t m_ms;  // Milliseconds

};

} // namespace mg
