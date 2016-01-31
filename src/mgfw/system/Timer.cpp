#include "Timer.h"

namespace mg {

Timer::Timer()
{}

bool Timer::update(Time t) {
    m_current += t;

    // If current exceeded its limit
    if(isFinished()) {
        // Round current time to fit the limit
        m_current = m_limit;

        return true;
    }
    else {
        return false;
    }
}

void Timer::reset() {
    m_current = Time();
}

void Timer::setCurrent(Time t) {
    m_current = t;
}

Time Timer::getCurrent() const {
    return m_current;
}

void Timer::setLimit(Time t) {
    m_limit = t;
}

Time Timer::getLimit() const {
    return m_limit;
}

void Timer::setCurrentAndLimit(Time t) {
    m_current = t;
    m_limit = t;
}

bool Timer::isFinished() const {
    return m_current >= m_limit;
}

} // namespace mg
