#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H

#include <list>
#include <ostream>

#include "pid.hpp"

namespace obd
{

class CarStatus
{
  public:
    CarStatus();
    typedef std::list<std::pair<pid::Pid_t, pid::Value_t>> Fields_t;
    void add_field(const pid::Pid_t &pid, const pid::Value_t &value);
    const Fields_t &get_fields() const;
  private:
    Fields_t fields_;
};

std::ostream &operator<<(std::ostream &os, const CarStatus &car_status);

} // namespace obd

#endif