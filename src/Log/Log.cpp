#include "Log.h"

Logger::Logger()
{
    Serial.begin(9600);
}

Logger Log = Logger();
