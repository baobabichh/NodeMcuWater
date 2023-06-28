#pragma once

#include "Log/Log.h"
#include <functional>
#include <string>
#include <ESP8266WebServer.h>

class Page
{
public:
    Page(const std::string &name, const std::function<void(void)> &handle);
    const std::string &getName() const;
    const std::function<void(void)>& getHandle() const;
    static ESP8266WebServer& server();
    static void setServer(ESP8266WebServer& server);


protected:
    const std::string m_name;
    const std::function<void(void)> m_handle;

private:
    static ESP8266WebServer * m_server;
};

#define CREATE_PAGE(class_name, url) \
namespace page_func\
{\
    void class_name##_func(void);\
}\
class class_name : public Page \
{ \
    static void run(void) { page_func::class_name##_func(void); } \
    class_name(); \
}; \
class_name::class_name() : Page(url, class_name::run) \
{ \
 \
} \
void page_func::class_name##_func(void) \


