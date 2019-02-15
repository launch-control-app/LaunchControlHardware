#include "pid.hpp"
namespace obd
{

namespace pid
{

Pid_groups_t group_pids(const Pids_t &pids)
{
    Pid_groups_t grouped_pids;
    for (auto pos = pids.begin(); pos != pids.end();)
        for (Pid_group_t pid_group;
             pid_group.size < GROUP_MAX_SIZE && pos != pids.end();
             pid_group.size++)
        {
            pid_group.pids[pid_group.size] = *(pos++);
            grouped_pids.push_back(pid_group);
        }

    return grouped_pids;
}

} // namespace pid

} // namespace obd