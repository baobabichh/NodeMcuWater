#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <string>
#include <sstream>

#define PRINT_LOGS
#include "Log/Log.h"

const char *ssid = "TP-LINK_2.4GHz_B9354B"; // replace with your wifi ssid and wpa2 key
const char *pass = "12qwaszx";
const char *hostname = "nodemcu-temperature";
ESP8266WebServer server;

void connect()
{
  Log << "Connecting to " << ssid << "\n";
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Log << ".";
  }
  Log << "Connected!\n";
  Log << "Local ip: " << WiFi.localIP() << '\n';
}

void handle_main_page()
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
  server.send(200, "text/html", page);
}

void handle_api_page()
{
  const bool d3 = digitalRead(FUNC_GPIO5);
  const short a0 = analogRead(PIN_A0);
  std::stringstream ss;
  ss << "{\"Digital\": \"" << d3 << "\", \"Analog\": \"" << a0 << "\"}";
  std::string str = ss.str();
  server.send(200, "text/html", str.c_str());
}

void handle_not_found()
{
  server.send(404, "text/plain", "Not found");
}

void startServer()
{
  server.onNotFound(handle_not_found);
  server.on("/", handle_main_page);

  server.on("/api", handle_api_page);

  server.begin();
}

void setup()
{
  pinMode(FUNC_GPIO0, INPUT);

  connect();

  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.begin();

  startServer();
}

void loop()
{
  ArduinoOTA.handle();
  server.handleClient();
}
