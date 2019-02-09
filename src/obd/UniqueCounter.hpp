#ifndef LAUNCHCONTROL_DATALOGGER_OBD_UNIQUECOUNTER_H
#define LAUNCHCONTROL_DATALOGGER_OBD_UNIQUECOUNTER_H

#include <Arduino.h>
#include <IntervalTimer.h>

namespace obd
{

class UniqueCounter
{
public:
  typedef uint64_t count_t;
  UniqueCounter() = delete;
  static void start();
  static void stop();
  static count_t getCount();
  static void reset();

private:
  static const uint16_t INTERVAL = 1000; // microseconds
  static IntervalTimer timer_;
  static volatile count_t count_;
  static void increment();
};

} // namespace obd
#endif