#include "breakpoint_counter.hpp"

namespace hw
{

BreakpointCounter::BreakpointCounter &BreakpointCounter::get_instance()
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
    timer_.begin(get_instance().increment, INTERVAL);
}

void BreakpointCounter::stop() { timer_.end(); }

const BreakpointCounter::Count_t BreakpointCounter::get_count()
{
    Count_t count;
    noInterrupts();
    count = count_;
    interrupts();
    return count;
}

const BreakpointCounter::Count_t BreakpointCounter::get_stall_count()
{
    Count_t count;
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