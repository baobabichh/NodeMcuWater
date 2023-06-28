#pragma once

#include "Water/IWaterer.h"
#include "Water/WaterSensor.h"
#include "Water/Pump.h"

class PortionWaterer : public IWaterer
{
public:
    void tick(uint32_t elapsed) override;
    void bindSensor(const WaterSensor &sensor);
    void bindPump(Pump &pump);

private:
    const WaterSensor *m_sensor = nullptr;
    Pump *m_pump = nullptr;

    uint16_t m_sensor_value_when_water = 0;
    uint32_t m_water_time = 0;

    uint32_t m_water_spend_time = 0;

    enum class Status : uint8_t
    {
        Waiting,
        Watering,
    };

    Status m_status = Status::Waiting;
};
