#include "obd_uart.hpp"

namespace hardware
{

ObdUart::Firmware_version_t ObdUart::begin()
{
    Firmware_version_t firmware_version = COBD::begin();
    while (!COBD::init())
        ;
    return firmware_version;
}

const ObdUart::Vin_t ObdUart::get_vin()
{
    char buffer[RECEIVE_BUFFER_SIZE];
    COBD::getVIN(buffer, RECEIVE_BUFFER_SIZE);
    return buffer;
}

const ObdUart::Pids_and_values_t ObdUart::read_pids(const Pids_t &pids)
{
    Pids_and_values_t pids_and_values;
    for (Pid_group_t &pid_group : group_pids(pids))
    {
        COBD::readPID(pid_group.pids.data(), pid_group.size,
                      pid_group.values.data());
        for (int i = 0; i < pid_group.size; i++)
            pids_and_values.emplace_back(pid_group.pids[i],
                                         pid_group.values[i]);
    }
    return pids_and_values;
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
