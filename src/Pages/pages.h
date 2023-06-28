#pragma once

#include "Page.h"
#include "System/Config.h"
#include "System/System.h"

#include <sstream>

class MainPage : public Page
{
public:
    static void run()
    {
        static const char *page =
            "<!DOCTYPE html>\n"
            "<html>\n"
            "\n"
            "<head>\n"
            "    <title>Real-time Updates</title>\n"
            "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js\"></script>\n"
            "    <script>\n"
            "\n"
            "        function parseJsonString(jsonString) {\n"
            "            try {\n"
            "                const parsedData = JSON.parse(jsonString);\n"
            "                const digitalValue = parsedData.Digital;\n"
            "                const analogValue = parsedData.Analog;\n"
            "                return [digitalValue, analogValue];\n"
            "            } catch (error) {\n"
            "                console.error('Error parsing JSON string:', error);\n"
            "                return null;\n"
            "            }\n"
            "        }\n"
            "        $(document).ready(function () {\n"
            "            // Function to update data\n"
            "            function updateData() {\n"
            "                $.ajax({\n"
            "                    url: '/api', // Replace with the actual URL of your data page\n"
            "                    success: function (data) {\n"
            "                        const [digitalValue, analogValue] = parseJsonString(data);\n"
            "\n"
            "                        $('#Digital').html(digitalValue);\n"
            "                        $('#Analog').html(analogValue);\n"
            "                    }\n"
            "                });\n"
            "            }\n"
            "\n"
            "            updateData();\n"
            "\n"
            "            setInterval(updateData, 1000);\n"
            "        });\n"
            "    </script>\n"
            "</head>\n"
            "\n"
            "<body>\n"
            "    <h1 id=\"Digital\"></h1>\n"
            "    <h1 id=\"Analog\"></h1>\n"
            "</body>\n"
            "\n"
            "</html>";
        server().send(200, "text/html", page);
    }

    MainPage() : Page("/", run)
    {
    }
};

class ApiPage : public Page
{
public:
    static void run()
    {
        const bool digit = System::getInstance().getWaterSensor().getDigitalValue();
        const short analog = System::getInstance().getWaterSensor().getAnalogValue();
        std::stringstream ss;
        ss << "{\"Digital\": \"" << digit << "\", \"Analog\": \"" << analog << "\"}";
        std::string str = ss.str();
        server().send(200, "text/html", str.c_str());
    }

    ApiPage() : Page("/api", run)
    {
    }
};

class SettingsPage : public Page
{
public:
    static void run()
    {
        if (server().arg("max_value") != "" && server().arg("submit") == "Submit")
        {
            auto val = server().arg("max_value");
            Config::getInstance().water_max_sensor_value = atoi(val.c_str());
        }

        std::stringstream ss;
        ss << "<!DOCTYPE html>\n"
              "<html lang=\"en\">\n"
              "<head>\n"
              "    <meta charset=\"UTF-8\">\n"
              "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
              "    <title>Document</title>\n"
              "</head>\n"
              "<body>\n"
              "    <h1>Current value: "
           << Config::getInstance().water_max_sensor_value << "</h1>\n";
        ss << "    <form action=\"/settings\">\n"
              "        <label>Input max value(0, 1024): </label>\n"
              "        <input type=\"number\" min=\"0\" max=\"1024\" name=\"max_value\">\n"
              "        <br>\n"
              "        <input type=\"submit\" name=\"submit\" value=\"Submit\"></input>\n"
              "    </form> \n"
              "</body>\n"
              "</html>";

        std::string str = ss.str();
        server().send(200, "text/html", str.c_str());
    }

    SettingsPage() : Page("/settings", run)
    {
    }
};

void handle_not_found()
{
    auto &server = Page::server();
    server.send(404, "text/plain", "Not found");
}