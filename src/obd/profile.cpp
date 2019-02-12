#include "profile.hpp"

namespace obd
{

void Profile::add_pid(const pid::Pid_t &pid, const Period_t &period)
{
    profile_[period].push_back(pid);
}

const Profile::Periods_t Profile::get_periods()
{
    Periods_t periods;
    for (const auto &profile_entry : profile_)
        periods.insert(profile_entry.first);
    return periods;
}

const pid::Pids_t Profile::get_pids(const Period_t &period)
{
    return profile_.at(period);
}

} // namespace obd