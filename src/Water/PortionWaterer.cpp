#include "PortionWaterer.h"

#include "Log/Log.h"

void PortionWaterer::tick(uint32_t elapsed)
{
    bool err = 0;
    if (!m_pump)
    {
        Log << "[PortionWaterer] No pump\n";
        err = 1;
    }
    if (!m_sensor)
    {
        Log << "[PortionWaterer] No sensor\n";
        err = 1;
    }
    if (err)
    {
        return;
    }

    if (Status::Waiting == m_status)
    {
        if (m_sensor->getAnalogValue() >= m_sensor_value_when_water)
        {
            m_pump->turnOn();
            m_status = Status::Watering;
        }
    }
    else if(Status::Watering == m_status)
    {
        m_water_spend_time += elapsed;
        if(m_water_spend_time >= m_water_time)
        {
            m_pump->turnOff();
            m_status = Status::Waiting;
        }
    }

}

void PortionWaterer::bindSensor(const WaterSensor &sensor)
{
    m_sensor = &sensor;
}

void PortionWaterer::bindPump(Pump &pump)
{
    m_pump = &pump;
}
