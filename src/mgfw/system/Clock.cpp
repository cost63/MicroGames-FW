#include "Clock.h"

#include <SDL2/SDL_timer.h>

namespace mg {

Clock::Clock()
: m_startTicks(SDL_GetTicks())
{}

Time Clock::restart() {
    uint32_t ticks = SDL_GetTicks();
    Time t = Time::Milliseconds(ticks - m_startTicks);

    m_startTicks = ticks;

    return t;
}

Time Clock::getElapsedTime() const {
    return Time::Milliseconds(SDL_GetTicks() - m_startTicks);
}

} // namespace mg
