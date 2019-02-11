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