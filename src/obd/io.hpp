/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Defines all IO objects used for the microcontroller
*/

#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_IO_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_IO_H

#include <sstream>
#include <numeric>

#include "hardware/obd_uart.hpp"
#include "hardware/bluetooth.hpp"
#include "profile.hpp"
#include "poller.hpp"

namespace obd
{

class Io
{
public:
  Io(hardware::Bluetooth &bluetooth, hardware::ObdUart obd_uart,
     hardware::BreakpointCounter &breakpoint_counter);
  void load_profile(const Profile& profile);
  void loop();

private:
  hardware::Bluetooth &bluetooth_;
  Poller poller_;
};

} // namespace obd

#endif