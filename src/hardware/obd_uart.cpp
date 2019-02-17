#include "obd_uart.hpp"

namespace hardware
{

const ObdUart::Pid_fields_t ObdUart::read_pids(const Pids_t &pids)
{
    Pid_fields_t pid_fields;
    for (Pid_group_t &pid_group : group_pids(pids))
    {
        readPID(pid_group.pids.data(), pid_group.size, pid_group.values.data());
        for (int i = 0; i < pid_group.size; i++)
            pid_fields.emplace_back(pid_group.pids[i], pid_group.values[i]);
    }
    return pid_fields;
}

ObdUart::Pid_groups_t ObdUart::group_pids(const Pids_t &pids)
{
    Pid_groups_t grouped_pids;
    for (auto pos = pids.begin(); pos != pids.end();)
        for (Pid_group_t pid_group;
             pid_group.size < PIDS_PER_GROUP && pos != pids.end();
             pid_group.size++)
        {
            pid_group.pids[pid_group.size] = *(pos++);
            grouped_pids.push_back(pid_group);
        }
    return grouped_pids;
}

} // namespace hardware
