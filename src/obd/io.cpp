#include "io.hpp"

namespace obd
{

Io::Io(hardware::Bluetooth &bluetooth, hardware::ObdUart obd_uart,
     hardware::BreakpointCounter &breakpoint_counter, const Profile &profile)
    :  bluetooth_(bluetooth), poller_(obd_uart, breakpoint_counter, profile) {}

void Io::loop()
{
    std::stringstream output;
    output << poller_.poll();
    bluetooth_.transmit(output.str().c_str());
}

} // namespace obd
