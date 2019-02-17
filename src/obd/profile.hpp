#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PROFILE_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PROFILE_H

#include <set>
#include <map>
#include <vector>

#include "stdint.h"

#include "hardware/obd_uart.hpp"

namespace obd
{

class Profile
{
  public:
    typedef uint32_t Period_t;
    typedef std::set<Period_t> Periods_t;
    Profile();
    void add_pid(const hardware::ObdUart::Pid_t &pid, const Period_t& period);
    const Periods_t get_periods() const;
    const hardware::ObdUart::Pids_t& get_pids(const Period_t &period) const;

  private:
    std::map<Period_t, hardware::ObdUart::Pids_t> profile_;
};

} // namespace obd

#endif