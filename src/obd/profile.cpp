#include "profile.hpp"

namespace obd
{

Profile::Profile() {}

void Profile::add_pid(const hardware::ObdUart::Pid_t &pid,
                      const Period_t &period)
{
    profile_[period].emplace_back(pid);
}

const Profile::Periods_t Profile::get_periods() const
{
    Periods_t periods;
    for (const auto &profile_entry : profile_)
        periods.emplace(profile_entry.first);
    return periods;
}

const hardware::ObdUart::Pids_t &Profile::get_pids(const Period_t &period) const
{
    return profile_.at(period);
}

} // namespace obd