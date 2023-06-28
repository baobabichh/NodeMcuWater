#pragma once

#include "Arduino.h"

#define PRINT_LOGS

class Logger
{
public:
    Logger();

    template <class T>
    Logger &operator<<(const T &obj)
    {
#ifdef PRINT_LOGS
        Serial.print(obj);
#endif
        return *this;
    }
};

extern Logger Log;
