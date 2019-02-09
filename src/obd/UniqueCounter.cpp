#include "UniqueCounter.hpp"

namespace obd
{

void UniqueCounter::start() { timer_.begin(increment, INTERVAL); }

void UniqueCounter::stop() { timer_.end(); }

UniqueCounter::count_t UniqueCounter::getCount()
{
  count_t count;
  noInterrupts();
  count = count_;
  interrupts();
  return count;
}

void UniqueCounter::reset()
{
  noInterrupts();
  count_ = 0;
  interrupts();
}

void UniqueCounter::increment() { count_++; }

} // namespace obd