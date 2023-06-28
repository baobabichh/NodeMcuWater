#include "Pump.h"

void Pump::begin(uint8_t d_pin)
{
    pinMode(m_d_pin, OUTPUT);
}

void Pump::turnOn()
{
    digitalWrite(m_d_pin, 1);
}

void Pump::turnOff()
{
    digitalWrite(m_d_pin, 0);
}

void Pump::turn(bool val)
{
    digitalWrite(m_d_pin, val);
}
