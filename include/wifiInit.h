#include <main.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ringDisplay.h>


//AP Configuration
#define AP_SSID     "ESP32-SmartControl"
#define AP_PASSWORD "12345678"

class wifiConfiguration{

    public:

    bool init();
    void printStatus();
    bool checkConnectivity();

};

extern wifiConfiguration wifi;