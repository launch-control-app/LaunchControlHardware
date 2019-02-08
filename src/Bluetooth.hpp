#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

#include "Hardware.hpp"

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

#endif