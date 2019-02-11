#include "profile.hpp"

namespace obd
{

void Profile::add_pid(pid::PID_t pid, PERIOD_t period)
{
    if (profile_.find(period) == profile_.end)
        profile_[period] = std::vector<pid::PID_t>{pid};
    else
        profile_[period].push_back(pid);
}

const Profile::PERIODs_t Profile::get_periods()
{
    PERIODs_t periods;
    for (const auto &profile_entry : profile_)
        periods.insert(profile_entry.first);
    return periods;
}

const pid::PIDs_t Profile::get_pids(PERIOD_t period)
{
    pid::PIDs_t pids;
    for (pid::PID_t &pid : profile_.at(period))
        pids.insert(pid);
}

} // namespace obd