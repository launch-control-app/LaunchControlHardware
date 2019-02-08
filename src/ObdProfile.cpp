#include "ObdProfile.hpp"

void ObdProfile::addPid(PID_t pid, PERIOD_t period)
{
    if (profile_.find(period) == profile_.end)
        profile_[period] = std::vector<ObdPolledPid>{ObdPolledPid(pid, period)};
    else
        profile_[period].push_back(ObdPolledPid(pid, period));
}

std::set<ObdProfile::PERIOD_t> ObdProfile::getPeriods()
{
    std::set<PERIOD_t> periods;
    for (const auto &profile_entry : profile_)
        periods.insert(profile_entry.first);
    return periods;
}