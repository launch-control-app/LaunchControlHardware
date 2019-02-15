#include "breakpoint_counter.hpp"

namespace hardware
{

BreakpointCounter &BreakpointCounter::get_instance()
{
    static BreakpointCounter breakpoint_counter;
    return breakpoint_counter;
}

void BreakpointCounter::set_breakpoints(const Breakpoints_t &breakpoints)
{
    breakpoints_ = breakpoints;
}

void BreakpointCounter::start()
{
    timer_.begin(BreakpointCounter::increment, INTERVAL);
}

void BreakpointCounter::stop() { timer_.end(); }

const BreakpointCounter::Count_t BreakpointCounter::get_count()
{
    Count_t count;
    stop();
    count = count_;
    start();
    return count;
}

const BreakpointCounter::Count_t BreakpointCounter::get_stall_count()
{
    Count_t count;
    stop();
    count = stall_count_;
    start();
    return count;
}

void BreakpointCounter::next_breakpoint()
{
    stop();
    if (++breakpoint_pos_ == breakpoints_.end())
        breakpoint_pos_ = breakpoints_.begin();
    current_breakpoint_ = *breakpoint_pos_;
    count_ = 0;
    stall_count_ = 0;
    start();
}

void BreakpointCounter::increment()
{
    BreakpointCounter breakpoint_counter = BreakpointCounter::get_instance();
    if (breakpoint_counter.count_ < breakpoint_counter.current_breakpoint_)
        breakpoint_counter.count_++;
    else
        breakpoint_counter.stall_count_++;
}

} // namespace hardware