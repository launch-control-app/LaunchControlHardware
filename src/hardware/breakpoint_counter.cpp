#include "breakpoint_counter.hpp"

namespace hardware
{

BreakpointCounter &BreakpointCounter::get_instance()
{
    static BreakpointCounter breakpoint_counter;
    return breakpoint_counter;
}

void BreakpointCounter::set_breakpoint(const Count_t &breakpoint)
{
    breakpoint_ = breakpoint;
    reached_breakpoint_ = false;
    reset_count();
}

void BreakpointCounter::start()
{
    timer_.begin(BreakpointCounter::increment, INTERVAL);
}

void BreakpointCounter::stop() { timer_.end(); }

// TODO: check if interrupts need to be disabled in this function
const bool BreakpointCounter::has_reached_breakpoint() const
{
    return reached_breakpoint_;
}

const BreakpointCounter::Count_t BreakpointCounter::get_count()
{
    return count_;
}

const BreakpointCounter::Count_t BreakpointCounter::get_stall_count()
{
    return stall_count_;
}

void BreakpointCounter::increment()
{
    BreakpointCounter breakpoint_counter = BreakpointCounter::get_instance();
    if (breakpoint_counter.count_ < breakpoint_counter.breakpoint_)
        if (++breakpoint_counter.count_ == breakpoint_counter.breakpoint_)
            breakpoint_counter.reached_breakpoint_ = true;
        else
            ++breakpoint_counter.stall_count_;
}

void BreakpointCounter::reset_count()
{
    count_ = 0;
    stall_count_ = 0;
}

} // namespace hardware