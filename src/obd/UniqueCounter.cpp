#include "Counter.hpp"

namespace obd
{

void Counter::start() { timer_.begin(increment, INTERVAL); }

void Counter::stop() { timer_.end(); }

Counter::count_t Counter::getCount()
{
  count_t count;
  noInterrupts();
  count = count_;
  interrupts();
  return count;
}

void Counter::reset()
{
  noInterrupts();
  count_ = 0;
  interrupts();
}

void Counter::increment() { count_++; }

} // namespace obd