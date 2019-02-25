#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PROFILE_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PROFILE_H

#include <set>
#include <map>
#include <vector>

#include "stdint.h"

#include "hardware/breakpoint_counter.hpp"
#include "hardware/obd_uart.hpp"

namespace obd
{

class Profile
{
public:
  using Pid_t = hardware::ObdUart::Pid_t;
  using Period_t = hardware::BreakpointCounter::Count_t;
  struct Pid_and_period_t
  {
    Pid_and_period_t(Pid_t pid, Period_t period) : pid(pid), period(period) {}
    Pid_t pid;
    Period_t period;
  };
  using Pids_and_periods_t = std::list<Pid_and_period_t>;
  Profile();
  void add_pid(const Pid_t &pid, const Period_t &period);
  const Pids_and_periods_t &get_pids_and_periods() const;
  const Period_t &get_period(const Pid_t &pid) const;

private:
  Pids_and_periods_t pids_and_periods_;
};

} // namespace obd

#endif