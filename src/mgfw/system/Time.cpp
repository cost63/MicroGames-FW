#include "Time.h"

namespace mg {

Time::Time()
: m_ms(0)
{}

Time::Time(uint32_t ms)
: m_ms(ms)
{}

/* Operators */

bool Time::operator==(Time other) const {
    return other.asMicroseconds() == m_ms;
}

bool Time::operator!=(Time other) const {
    return !Time::operator==(other);
}

bool Time::operator>(Time other) const {
    return other.asMilliseconds() > m_ms;
}

bool Time::operator>=(Time other) const {
    return other.asMilliseconds() >= m_ms;
}

bool Time::operator<(Time other) const {
    return other.asMilliseconds() < m_ms;
}

bool Time::operator<=(Time other) const {
    return other.asMilliseconds() <= m_ms;
}

Time Time::operator+(Time other) const {
    return Time(m_ms + other.asMilliseconds());
}

Time& Time::operator+=(Time other) {
    return *this = (*this + other);
}

Time Time::operator-(Time other) const {
    if(other.asMilliseconds() > m_ms) {
        return Time(0);
    }
    else {
        return Time(m_ms - other.asMilliseconds());
    }
}

Time& Time::operator-=(Time other) {
    if(other.asMilliseconds() > m_ms) {
        m_ms = 0;
        return *this;
    }
    else {
        m_ms -= other.asMilliseconds();
        return *this;
    }
}

Time Time::operator*(Time other) const {
    return Time(m_ms * other.asMilliseconds());
}

Time& Time::operator*=(Time other) {
    return *this = (*this * other);
}

Time Time::operator/(Time other) const {
    return Time(m_ms / other.asMilliseconds());
}

Time& Time::operator/=(Time other) {
    return *this = (*this / other);
}

/* Methods */

float Time::asSeconds() const {
    return (float)m_ms / 1000;
}

uint32_t Time::asMilliseconds() const {
    return m_ms;
}

uint64_t Time::asMicroseconds() const {
    return m_ms * 1000;
}

/* Static methods */

Time Time::Seconds(float s) {
    return Time(s * 1000);
}

Time Time::Milliseconds(uint32_t ms) {
    return Time(ms);
}

Time Time::Microseconds(uint64_t ms) {
    return Time(ms / 1000);
}

} // namespace mg
