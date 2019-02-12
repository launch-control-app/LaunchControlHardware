#ifndef LAUNCHCONTROL_DATALOGGER_OBD_PID_H
#define LAUNCHCONTROL_DATALOGGER_OBD_PID_H

#include <vector>
#include <stdint.h>

namespace obd
{

namespace pid
{

typedef uint8_t Pid_t;
typedef std::vector<Pid_t> Pids_t;
typedef int Value_t;

} // namespace pid

} // namespace obd

#endif