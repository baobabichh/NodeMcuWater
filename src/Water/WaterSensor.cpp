#include "WaterSensor.h"

void WaterSensor::begin(uint8_t d_pin, uint8_t a_pin)
{
    m_d_pin = d_pin;
    m_a_pin = a_pin;

    pinMode(m_d_pin, INPUT);
    pinMode(m_a_pin, INPUT);
}

uint16_t WaterSensor::getAnalogValue() const
{
    return 1024 - analogRead(m_a_pin);
}

bool WaterSensor::getDigitalValue() const
{
    return !digitalRead(m_d_pin);
}