#ifndef LAUNCHCONTROL_DATALOGGER_OBD_PID_H
#define LAUNCHCONTROL_DATALOGGER_OBD_PID_H

#include <set>
#include <stdint.h>

namespace obd
{

namespace pid
{

typedef const uint8_t PID_t;
typedef std::set<PID_t> PIDs_t;
typedef int Value_t;

} // namespace pid

} // namespace obd

#endif