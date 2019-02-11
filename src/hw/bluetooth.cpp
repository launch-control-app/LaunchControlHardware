#include "bluetooth.hpp"

namespace hw
{

Bluetooth::Bluetooth(HardwareSerial &uart, PIN_t CMD_PIN,
                     PIN_t STATE_PIN_, uint32_t baud)
    : uart_(uart), CMD_PIN_(CMD_PIN), STATE_PIN_(STATE_PIN_), baud_(baud)
{
  uart_.begin(baud_);
}

Bluetooth::~Bluetooth()
{
  uart_.end();
}

void Bluetooth::transmit(const String msg)
{
  uart_.println(msg);
}

bool Bluetooth::connected()
{
  return digitalRead(STATE_PIN_);
}

} // namespace hw
