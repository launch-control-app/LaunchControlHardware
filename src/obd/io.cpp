/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Implements the high level IO class
*/

#include "io.hpp"

namespace obd
{

Io::Io(hardware::Bluetooth &bluetooth, hardware::ObdUart obd_uart,
       hardware::BreakpointCounter &breakpoint_counter)
    : bluetooth_(bluetooth), poller_(obd_uart, breakpoint_counter) {}

void Io::load_profile(const Profile &profile)
{
    poller_.load_profile(profile);
}

void Io::loop()
{
    poller_.poll();
    std::stringstream output;
    output << poller_.get_car_status();
    bluetooth_.transmit(output.str());
}

} // namespace obd
