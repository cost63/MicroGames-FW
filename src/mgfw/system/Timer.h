#pragma once

#include "../system/Time.h"

namespace mg {

class Timer {
public:
    Timer();

    bool update(Time t);
    void reset();

    void setCurrent(Time t);
    Time getCurrent() const;

    void setLimit(Time t);
    Time getLimit() const;

    void setCurrentAndLimit(Time t);

    bool isFinished() const;

private:
    Time m_current;
    Time m_limit;

};

} // namespace mg
