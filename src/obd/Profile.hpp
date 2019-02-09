#ifndef LAUNCHCONTROL_DATALOGGER_OBD_PROFILE_H
#define LAUNCHCONTROL_DATALOGGER_OBD_PROFILE_H

#include <set>
#include <map>
#include <vector>

#include "stdint.h"

#include "Pid.hpp"

namespace obd
{

class Profile
{
public:
  typedef const uint32_t PERIOD_t;
  void addPid(pid::PID_t pid, PERIOD_t period);
  std::set<PERIOD_t> getPeriods();

private:
  std::map<PERIOD_t, std::vector<pid::PID_t>> profile_;
};

} // namespace obd

#endif