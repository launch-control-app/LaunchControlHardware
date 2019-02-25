#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BREAKPOINT_COUNTER_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BREAKPOINT_COUNTER_H

#include <list>

#include <Arduino.h>
#include <IntervalTimer.h>

namespace hardware
{

class BreakpointCounter
{
  public:
    using Count_t = uint64_t;
    static BreakpointCounter &get_instance();
    void set_breakpoint(const Count_t &breakpoint);
    void start();
    void stop();
    const bool has_reached_breakpoint() const;
    const Count_t get_count();
    const Count_t get_stall_count();

  private:
    static const uint16_t INTERVAL = 1000; // microseconds
    BreakpointCounter() = default;
    static void increment();
    void reset_count();
    IntervalTimer timer_;
    Count_t breakpoint_;
    volatile boolean reached_breakpoint_;
    volatile Count_t count_;
    volatile Count_t stall_count_;
};

} // namespace hardware

#endif