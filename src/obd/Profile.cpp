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

Profile::PERIODS_t Profile::get_periods()
{
    std::set<PERIOD_t> periods;
    for (const auto &profile_entry : profile_)
        periods.insert(profile_entry.first);
    return periods;
}

} // namespace obd