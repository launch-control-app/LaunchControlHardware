#ifndef LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BLUETOOTH_H
#define LAUNCH_CONTROL_DATA_COLLECTOR_HARDWARE_BLUETOOTH_H

#include <Arduino.h>

#include "hardware.hpp"

namespace hardware
{

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial &uart, PIN_t CMD_PIN,
              PIN_t STATE_PIN, uint32_t baud);
    ~Bluetooth();
    void transmit(const String msg);
    const bool is_connected() const;

  private:
    HardwareSerial &uart_;
    PIN_t CMD_PIN_;
    PIN_t STATE_PIN_;
    uint32_t baud_;
};

} // namespace hardware

#endif