#include "poller.hpp"

namespace obd
{

Poller::Poller(hardware::ObdUart &obd_uart,
               hardware::BreakpointCounter &breakpoint_counter,
               const Profile &profile)
    : obd_uart_(obd_uart), breakpoint_counter_(breakpoint_counter)
{
    load_profile(profile);
}

void Poller::load_profile(const Profile &profile)
{
    profile_ = profile;
    profile_.get_periods();
    // TODO: load breakpoints into counter
}

const CarStatus Poller::poll()
{
    return CarStatus(obd_uart_.read_pids(profile_.get_pids(breakpoint_counter_.get_count())));
    // TODO: check counter using a bool 
}

} // namespace obd