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
  typedef std::set<PERIOD_t> PERIODs_t;
  void add_pid(pid::PID_t pid, PERIOD_t period);
  const PERIODs_t get_periods();
  const pid::PIDs_t get_pids(PERIOD_t period);
  
private:
  std::map<PERIOD_t, std::vector<pid::PID_t>> profile_;
};

} // namespace obd

#endif