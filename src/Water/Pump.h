#pragma once

#include "Log/Log.h"

class Pump
{
private:
    uint8_t m_d_pin = D0;
public:
    void begin(uint8_t d_pin);
    void turnOn();
    void turnOff();
    void turn(bool val);
};
