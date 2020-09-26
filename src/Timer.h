#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    using clock_t = std::chrono::high_resolution_clock;
    using duration_t = std::chrono::microseconds;

    std::chrono::time_point<clock_t> m_beginning;

    void reset();
    int get() const;
};



#endif /* TIMER_H */
