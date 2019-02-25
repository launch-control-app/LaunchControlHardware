#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BLUETOOTH_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BLUETOOTH_H

#include <string>

#include <Arduino.h>

#include "hardware.hpp"

namespace hardware
{

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial &uart, const PIN_t &cmd_pin,
              const PIN_t &state_pin, const uint32_t &baud);
    ~Bluetooth();
    void begin();
    void transmit(const std::string &msg);
    const bool is_connected();

  private:
    HardwareSerial &uart_;
    PIN_t cmd_pin_;
    PIN_t state_pin_;
    uint32_t baud_;
};

} // namespace hardware

#endif