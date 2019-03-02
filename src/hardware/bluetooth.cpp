/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Defines a bluetooth interface for transmitting data
*/

#include "bluetooth.hpp"

namespace hardware
{

Bluetooth::Bluetooth(HardwareSerial &uart, const PIN_t &cmd_pin,
                     const PIN_t &state_pin_, const uint32_t &baud)
    : uart_(uart), cmd_pin_(cmd_pin), state_pin_(state_pin_), baud_(baud) {}

void Bluetooth::begin()
{
    uart_.begin(baud_);
    pinMode(state_pin_, INPUT);
}

Bluetooth::~Bluetooth() { uart_.end(); }

void Bluetooth::transmit(const std::string &msg) { uart_.println(msg.c_str()); }

const bool Bluetooth::is_connected() { return digitalRead(state_pin_); }

} // namespace hardware
