#ifndef LAUNCHCONTROL_DATALOGGER_HW_BLUETOOTH_H
#define LAUNCHCONTROL_DATALOGGER_HW_BLUETOOTH_H

#include <Arduino.h>

#include "hardware.hpp"

namespace hw
{

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial &uart, PIN_t CMD_PIN,
              PIN_t STATE_PIN, uint32_t baud);
    ~Bluetooth();
    void transmit(const String msg);
    bool connected();

  private:
    HardwareSerial &uart_;
    PIN_t CMD_PIN_;
    PIN_t STATE_PIN_;
    uint32_t baud_;
};

} // namespace hw

#endif