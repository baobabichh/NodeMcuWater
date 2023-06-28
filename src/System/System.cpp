#include "System.h"
#include "Pages/pages.h"

void System::setup()
{
    m_sensor.begin(D3, A0);

    pinMode(D5, OUTPUT);

    connect();

    static const char *hostname = "nodemcu-temperature";
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA.begin();

    setupServer();
}

void System::loop()
{
    uint32_t elapsed = millis() - m_time;
    tick(elapsed);
}

void System::tick(uint32_t elapsed)
{
    digitalWrite(D5, 1);
    ArduinoOTA.handle();
    m_server.handleClient();
}

void System::connect()
{
    static constexpr const char *wifi = "TP-LINK_2.4GHz_B9354B";
    static constexpr const char *pass = "12qwaszx";

    Log << "Connecting to " << wifi << "\n";
    WiFi.begin(wifi, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Log << ".";
    }
    Log << "Connected!\n";
    Log << "Local ip: " << WiFi.localIP() << '\n';
}

void System::setupServer()
{
    m_server.onNotFound(handle_not_found);
    addPage(MainPage());
    addPage(SettingsPage());
    addPage(ApiPage());

    m_server.begin();
    Page::setServer(m_server);
}

void System::addPage(const Page &page)
{
    m_server.on(page.getName().c_str(), page.getHandle());
}
