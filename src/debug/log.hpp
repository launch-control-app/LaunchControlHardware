#ifndef LAUNCHCONTROL_DATALOGGER_DEBUG_LOG_H
#define LAUNCHCONTROL_DATALOGGER_DEBUG_LOG_H

#include <Arduino.h>

namespace debug
{

class Log
{
  public:
    void static info(const String msg);
    void static error(const String msg);
    void static log(const String tag, const String msg);

  private:
    const static uint32_t BAUD = 9600; // PlatformIO serial monitor default
    static bool started;
};

} // namespace debug

#endif