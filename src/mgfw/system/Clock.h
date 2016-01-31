#pragma once

#include "../system/Time.h"

namespace mg {

class Clock {
public:
    Clock();

    Time restart();
    Time getElapsedTime() const;

private:
    uint32_t m_startTicks;

};

} // namespace mg
