/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Implements a logging interface for testing
*/

#include "log.hpp"

namespace debug
{

bool Log::started = false;

void Log::info(const String msg)
{
    log("INFO", msg);
}

void Log::error(const String msg)
{
    log("ERROR", msg);
}

void Log::log(const String tag, const String msg)
{
    if (!started)
    {
        Serial.begin(BAUD);
        started = true;
    }
    Serial.println(tag + ": " + msg);
}

} // namespace debug