#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_POLLER_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_POLLER_H

#include <sstream>

#include "hardware/breakpoint_counter.hpp"
#include "hardware/obd_uart.hpp"
#include "profile.hpp"
#include "car_status.hpp"

namespace obd
{

class Poller
{
public:
  Poller(hardware::ObdUart &obd_uart,
         hardware::BreakpointCounter &breakpoint_counter);
  void load_profile(const Profile &profile);
  void poll();
  const CarStatus &get_car_status();

private:
  void set_next_breakpoint();
  hardware::ObdUart &obd_uart_;
  hardware::BreakpointCounter &breakpoint_counter_;
  CarStatus car_status_;
};

} // namespace obd

#endif