/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Implements a car status object that maintains the existing
  profile and updates values
*/

#include "car_status.hpp"

namespace obd
{

void CarStatus::load_profile(const Profile &profile)
{
    profile_ = profile;
    min_remaining_period_.valid = false;
    for (const Pid_and_period_t &pid_and_period :
         profile_.get_pids_and_periods())
    {
        pids_to_update_.emplace_back(pid_and_period.pid);
        add_pid_and_period(pid_and_period);
        update_min_period(pid_and_period.period);
    }
}

const CarStatus::Period_t &CarStatus::get_min_remaining_period() const
{
    return min_remaining_period_.period;
}

const CarStatus::Pids_t &CarStatus::get_pids_to_update() const
{
    return pids_to_update_;
}

void CarStatus::update(const Pids_and_values_t &&pids_and_values)
{
    update_pids_and_values(std::move(pids_and_values));
    update_periods(min_remaining_period_.period);
}

const CarStatus::Pids_and_values_t &
CarStatus::get_updated_pids_and_values() const
{
    return updated_pids_and_values_;
}

void CarStatus::add_pid_and_period(const Pid_and_period_t &pid_and_period)
{
    pids_and_remaining_periods_.emplace_back(pid_and_period.pid,
                                             pid_and_period.period);
}

void CarStatus::update_pids_and_values(const Pids_and_values_t &&pids_and_values)
{
    pids_to_update_.clear();
    updated_pids_and_values_ = pids_and_values;
}

void CarStatus::update_periods(const Period_t &amount)
{
    min_remaining_period_.valid = false;
    for (auto &pid_and_remaining_period : pids_and_remaining_periods_)
    {
        decrease_period(pid_and_remaining_period, amount);
        update_min_period(pid_and_remaining_period.period);
    }
}

void CarStatus::decrease_period(Pid_and_period_t &pid_and_remaining_period,
                                const Period_t &amount)
{
    if ((pid_and_remaining_period.period -= amount) <= 0)
    {
        pids_to_update_.emplace_back(pid_and_remaining_period.pid);
        pid_and_remaining_period.period =
            profile_.get_period(pid_and_remaining_period.pid);
    }
}

void CarStatus::update_min_period(const Period_t &period)
{
    if (min_remaining_period_.valid == false ||
        period < min_remaining_period_.period)
    {
        min_remaining_period_.period = period;
        min_remaining_period_.valid = true;
    }
}

// TODO: fix output formatting once bluetooth data message
//  format has been finalized
std::ostream &operator<<(std::ostream &os, const CarStatus &car_status)
{
    for (const auto &pid_and_value : car_status.get_updated_pids_and_values())
        os << pid_and_value.value << ",";
    return os;
}

} // namespace obd