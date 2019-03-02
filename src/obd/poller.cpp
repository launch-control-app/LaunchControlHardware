/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Implements a poller that contains a profile and 
  breakpoint counter
*/

#include "poller.hpp"

namespace obd
{

Poller::Poller(hardware::ObdUart &obd_uart,
               hardware::BreakpointCounter &breakpoint_counter)
    : obd_uart_(obd_uart), breakpoint_counter_(breakpoint_counter) {}

void Poller::load_profile(const Profile &profile)
{
    car_status_.load_profile(profile);
    breakpoint_counter_.set_breakpoint(1); // TODO: Get rid of magic number
    breakpoint_counter_.start();
}

void Poller::poll()
{
    if (breakpoint_counter_.has_reached_breakpoint())
    {
        set_next_breakpoint();
        car_status_.update(obd_uart_.read_pids(
            car_status_.get_pids_to_update()));
    }
}

const CarStatus &Poller::get_car_status()
{
    return car_status_;
}

void Poller::set_next_breakpoint()
{
    breakpoint_counter_.stop();
    breakpoint_counter_.set_breakpoint(
        car_status_.get_min_remaining_period());
    breakpoint_counter_.start();
}

} // namespace obd