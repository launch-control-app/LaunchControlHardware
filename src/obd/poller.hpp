#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_POLLER_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_POLLER_H

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
         hardware::BreakpointCounter &breakpoint_counter,
         const Profile &profile);
  void load_profile(const Profile &profile);
  const CarStatus poll();

private:
  hardware::ObdUart &obd_uart_;
  hardware::BreakpointCounter &breakpoint_counter_;
  Profile profile_;
};

} // namespace obd

#endif