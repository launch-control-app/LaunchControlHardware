#include "breakpoint_counter.hpp"

namespace obd
{

void BreakpointCounter::set_breakpoints(const breakpoints_t &breakpoints)
{
    breakpoints_ = breakpoints;
}

void BreakpointCounter::start() { timer_.begin(increment, INTERVAL); }

void BreakpointCounter::stop() { timer_.end(); }

BreakpointCounter::count_t BreakpointCounter::get_count()
{
    count_t count;
    noInterrupts();
    count = count_;
    interrupts();
    return count;
}

BreakpointCounter::count_t BreakpointCounter::get_stall_count()
{
    count_t count;
    noInterrupts();
    count = stall_count_;
    interrupts();
    return count;
}

void BreakpointCounter::next_breakpoint()
{
    noInterrupts();
    if (++breakpoint_pos_ == breakpoints_.end)
        breakpoint_pos_ = breakpoints_.begin;
    current_breakpoint_ = *breakpoint_pos_;
    count_ = 0;
    stall_count_ = 0;
    interrupts();
}

void BreakpointCounter::increment()
{
    count_ < current_breakpoint_ ? count_++ : stall_count_++;
}

} // namespace obd