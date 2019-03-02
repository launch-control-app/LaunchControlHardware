/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Defines a car status object that maintains the existing
  profile and updates values
*/

#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_CAR_STATUS_H

#include <map>
#include <list>
#include <ostream>

#include "hardware/obd_uart.hpp"
#include "profile.hpp"

namespace obd
{

class CarStatus
{
  public:
    using Pids_t = hardware::ObdUart::Pids_t;
    using Pids_and_values_t = hardware::ObdUart::Pids_and_values_t;
    using Period_t = Profile::Period_t;
    CarStatus() = default;
    void load_profile(const Profile &profile);
    const Period_t &get_min_remaining_period() const;
    const Pids_t &get_pids_to_update() const;
    void update(const Pids_and_values_t &&pids);
    const Pids_and_values_t &get_updated_pids_and_values() const;

  private:
    using Pid_and_period_t = Profile::Pid_and_period_t;
    using Pids_and_periods_t = Profile::Pids_and_periods_t;
    struct
    {
        Period_t period;
        boolean valid;
    } min_remaining_period_;
    void add_pid_and_period(const Pid_and_period_t &pid_and_period);
    void update_pids_and_values(const Pids_and_values_t &&pids);
    void update_periods(const Period_t &amount);
    void decrease_period(Pid_and_period_t &pid_and_remaining_period,
                         const Period_t &amount);
    void update_min_period(const Period_t &period);
    Profile profile_;
    Pids_t pids_to_update_;
    Pids_and_periods_t pids_and_remaining_periods_;
    Pids_and_values_t updated_pids_and_values_;
};

std::ostream &operator<<(std::ostream &os, const CarStatus &car_status);

} // namespace obd

#endif