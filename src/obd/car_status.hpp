#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H

#include <list>
#include <ostream>

#include "hardware/obd_uart.hpp"

namespace obd
{

class CarStatus
{
public:
  explicit CarStatus(const hardware::ObdUart::Pid_fields_t &pid_fields);
  const hardware::ObdUart::Pid_fields_t &get_fields() const;

private:
  hardware::ObdUart::Pid_fields_t pid_fields_;
};

std::ostream &operator<<(std::ostream &os, const CarStatus &car_status);

} // namespace obd

#endif