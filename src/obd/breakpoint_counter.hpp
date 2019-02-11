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
    BreakpointCounter() = delete;
    static void set_breakpoints(const breakpoints_t &breakpoints);
    static void start();
    static void stop();
    static count_t get_count();
    static count_t get_stall_count();
    static void next_breakpoint();

  private:
    static const uint16_t INTERVAL = 1000; // microseconds
    static void increment();
    static IntervalTimer timer_;
    static breakpoints_t breakpoints_;
    static breakpoints_t::iterator breakpoint_pos_;
    static breakpoint_t current_breakpoint_;
    static volatile count_t count_;
    static volatile count_t stall_count_;
};

} // namespace obd

#endif