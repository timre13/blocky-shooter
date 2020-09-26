#include "Timer.h"

void Timer::reset()
{
    m_beginning = clock_t::now();
}

int Timer::get() const
{
    return std::chrono::duration_cast<duration_t>(clock_t::now() - m_beginning).count();
}
