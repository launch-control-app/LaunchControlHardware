#ifndef OBDPROFILE_H
#define OBDPROFILE_H

#include <set>
#include <map>
#include <vector>

#include "stdint.h"

class ObdProfile
{
public:
  typedef const uint8_t PID_t;
  typedef const uint32_t PERIOD_t;
  void addPid(PID_t pid, PERIOD_t period);
  std::set<PERIOD_t> getPeriods();

private:
  struct ObdPolledPid
  {
    ObdPolledPid(PID_t aPid, PERIOD_t aPeriod) : pid(aPid), period(aPeriod) {}
    PID_t pid;
    PERIOD_t period;
  };
  std::map<PERIOD_t, std::vector<ObdPolledPid>> profile_;
};

#endif