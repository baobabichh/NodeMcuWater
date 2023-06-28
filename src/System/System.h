#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <string>
#include <sstream>
#include "Pages/Page.h"

#include "Water/WaterSensor.h"

#define PRINT_LOGS
#include "Log/Log.h"

class System
{
public:
    void setup();
    void loop();

    static System& getInstance()
    {
        static System s;
        return s;
    }

    inline WaterSensor& getWaterSensor()
    {
        return m_sensor;
    }

private:
    void tick(uint32_t elapsed);

    void connect();
    void setupServer();
    void addPage(const Page &page);

private:
    System() = default;
    unsigned long m_time = 0;

    ESP8266WebServer m_server;
    WaterSensor m_sensor;
};