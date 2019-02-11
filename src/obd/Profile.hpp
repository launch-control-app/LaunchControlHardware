#ifndef LAUNCHCONTROL_DATALOGGER_OBD_PROFILE_H
#define LAUNCHCONTROL_DATALOGGER_OBD_PROFILE_H

#include <set>
#include <map>
#include <vector>

#include "stdint.h"

#include "pid.hpp"

namespace obd
{

class Profile
{
public:
  typedef const uint32_t PERIOD_t;
  typedef const std::set<PERIOD_t> PERIODS_t;
  void add_pid(pid::PID_t pid, PERIOD_t period);
  PERIODS_t get_periods();
  
private:
  std::map<PERIOD_t, std::vector<pid::PID_t>> profile_;
};

} // namespace obd

#endif