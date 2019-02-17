#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_OBD_UART_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_OBD_UART_H

#include <array>
#include <list>

#include <OBD2UART.h>

namespace hardware
{

class ObdUart : private COBD
{
public:
  typedef uint8_t Pid_t;
  typedef std::list<Pid_t> Pids_t;
  typedef int Pid_value_t;
  typedef std::pair<Pid_t, Pid_value_t> Pid_field_t;
  typedef std::list<Pid_field_t> Pid_fields_t;
  const Pid_fields_t read_pids(const Pids_t &pids);
  // TODO: read_vin()

private:
  static const uint8_t PIDS_PER_GROUP = 8;
  struct Pid_group_t
  {
    std::array<Pid_t, PIDS_PER_GROUP> pids;
    std::array<Pid_value_t, PIDS_PER_GROUP> values;
    uint8_t size = 0;
  };
  typedef std::list<Pid_group_t> Pid_groups_t;
  Pid_groups_t group_pids(const Pids_t &pids);
};

} // namespace hardware

#endif