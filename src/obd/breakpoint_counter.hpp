#ifndef LAUNCHCONTROL_DATALOGGER_BREAKPOINTCOUNTER_H
#define LAUNCHCONTROL_DATALOGGER_BREAKPOINTCOUNTER_H

#include <list>

#include <Arduino.h>
#include <IntervalTimer.h>

namespace obd
{

class BreakpointCounter
{
  public:
    typedef uint64_t count_t;
    typedef count_t breakpoint_t;
    typedef std::list<breakpoint_t> breakpoints_t;
    static BreakpointCounter& get_instance();
    void set_breakpoints(const breakpoints_t &breakpoints);
    void start();
    void stop();
    count_t get_count();
    count_t get_stall_count();
    void next_breakpoint();

  private:
    static const uint16_t INTERVAL = 1000; // microseconds
    BreakpointCounter() {};
    void increment();
    IntervalTimer timer_;
    breakpoints_t breakpoints_;
    breakpoints_t::iterator breakpoint_pos_;
    breakpoint_t current_breakpoint_;
    volatile count_t count_;
    volatile count_t stall_count_;
};

} // namespace obd

#endif