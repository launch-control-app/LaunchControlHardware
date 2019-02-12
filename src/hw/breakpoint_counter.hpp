#ifndef LAUNCHCONTROL_DATALOGGER_HW_BREAKPOINTCOUNTER_H
#define LAUNCHCONTROL_DATALOGGER_HW_BREAKPOINTCOUNTER_H

#include <list>

#include <Arduino.h>
#include <IntervalTimer.h>

namespace hw
{

namespace breakpoint_counter { void increment(); }

class BreakpointCounter
{
  public:
    typedef uint64_t Count_t;
    typedef Count_t Breakpoint_t;
    typedef std::list<Breakpoint_t> Breakpoints_t;
    static BreakpointCounter &get_instance();
    void set_breakpoints(const Breakpoints_t &breakpoints);
    void start();
    void stop();
    const Count_t get_count();
    const Count_t get_stall_count();
    void next_breakpoint();

  private:
    static const uint16_t INTERVAL; // microseconds
    BreakpointCounter(){};
    friend void breakpoint_counter::increment();
    IntervalTimer timer_;
    Breakpoints_t breakpoints_;
    Breakpoints_t::iterator breakpoint_pos_;
    Breakpoint_t current_breakpoint_;
    volatile Count_t count_;
    volatile Count_t stall_count_;
};

} // namespace hw

#endif