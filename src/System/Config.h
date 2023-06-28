#pragma once

#include "Log/Log.h"

class Config
{
public:

    static Config& getInstance()
    {
        static Config cfg;
        return cfg;
    }

    uint32_t water_max_sensor_value = 1024;

private:
    Config() = default;
};
