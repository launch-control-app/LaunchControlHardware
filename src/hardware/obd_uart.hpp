/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Defines an encapsulation of the provided OBD-II library 
*/

#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_OBD_UART_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_OBD_UART_H

#include <string>
#include <array>
#include <list>

#include <OBD2UART.h>

namespace hardware
{

class ObdUart : private COBD
{
public:
  using Firmware_version_t = byte;
  using Vin_t = std::string;
  using Pid_t = uint8_t;
  using Pids_t = std::list<Pid_t>;
  using Pid_value_t = int;
  struct Pid_and_value_t
  {
    Pid_and_value_t(Pid_t pid, Pid_value_t pid_value) : pid(pid), value(pid_value) {}
    Pid_t pid;
    Pid_value_t value;
  };
  using Pids_and_values_t = std::list<Pid_and_value_t>;
  Firmware_version_t begin();
  const Vin_t get_vin();
  const Pids_and_values_t read_pids(const Pids_t &pids);

private:
  static const uint8_t RECEIVE_BUFFER_SIZE = 64;
  static const uint8_t PIDS_PER_GROUP = 8;
  struct Pid_group_t
  {
    std::array<Pid_t, PIDS_PER_GROUP> pids;
    std::array<Pid_value_t, PIDS_PER_GROUP> values;
    uint8_t size = 0;
  };
  using Pid_groups_t = std::list<Pid_group_t>;
  Pid_groups_t group_pids(const Pids_t &pids);
};

} // namespace hardware

#endif