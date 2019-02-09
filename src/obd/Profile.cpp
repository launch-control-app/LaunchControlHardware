#include "Profile.hpp"

namespace obd
{

void Profile::addPid(pid::PID_t pid, PERIOD_t period)
{
    if (profile_.find(period) == profile_.end)
        profile_[period] = std::vector<pid::PID_t>{pid};
    else
        profile_[period].push_back(pid);
}

std::set<Profile::PERIOD_t> Profile::getPeriods()
{
    std::set<PERIOD_t> periods;
    for (const auto &profile_entry : profile_)
        periods.insert(profile_entry.first);
    return periods;
}

} // namespace obd