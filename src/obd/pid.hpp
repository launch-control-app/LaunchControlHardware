#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PID_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_OBD_PID_H

#include <list>
#include <array>
#include <iterator>
#include <stdint.h>

namespace obd
{

namespace pid
{
const uint8_t GROUP_MAX_SIZE = 8;

typedef uint8_t Pid_t;
typedef std::list<Pid_t> Pids_t;
typedef int Value_t;
struct Pid_group_t
{
    std::array<Pid_t, GROUP_MAX_SIZE> pids;
    std::array<Value_t, GROUP_MAX_SIZE> values;
    uint8_t size = 0;
};
typedef std::list<Pid_group_t> Pid_groups_t;

Pid_groups_t group_pids(Pids_t pids);


} // namespace pid

} // namespace obd

#endif