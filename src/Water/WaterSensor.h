#pragma once

#include "Log/Log.h"


class WaterSensor
{
private:
    uint8_t m_d_pin = D0;
    uint8_t m_a_pin = A0;
public:
    void begin(uint8_t d_pin, uint8_t a_pin);
    uint16_t getAnalogValue()const;
    bool getDigitalValue()const;
};