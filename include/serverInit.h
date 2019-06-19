#include <main.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

class serverConfiguration{

    public:

    void init(void);
    void handleClient();
};

extern AsyncWebServer localServer;
extern serverConfiguration server;