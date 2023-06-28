#include "Page.h"

ESP8266WebServer * Page::m_server = nullptr;

Page::Page(const std::string &name, const std::function<void(void)> &handle) : m_name(name), m_handle(handle)
{
}

const std::string &Page::getName() const
{
    return m_name;
}

const std::function<void(void)>& Page::getHandle() const
{
    return m_handle;
}

ESP8266WebServer &Page::server()
{
    if(!m_server)
    {
        Log << "[Page] no server\n";
    }

    return *m_server;
}

void Page::setServer(ESP8266WebServer &server)
{
    m_server = &server;
}
