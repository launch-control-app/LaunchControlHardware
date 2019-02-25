#include "profile.hpp"

namespace obd
{

Profile::Profile() {}

void Profile::add_pid(const Pid_t &pid, const Period_t &period)
{
    pids_and_periods_.emplace_back(pid, period);
}

const Profile::Pids_and_periods_t &Profile::get_pids_and_periods() const
{
    return pids_and_periods_;
}

const Profile::Period_t &Profile::get_period(const Pid_t &pid) const
{
    for (const auto &pid_and_period : pids_and_periods_)
        if (pid_and_period.pid == pid)
            return pid_and_period.period;
}

} // namespace obd