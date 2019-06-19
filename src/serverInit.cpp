#include <serverInit.h>

AsyncWebServer localServer(80);
WiFiClient localClient;

serverConfiguration server;

String _userSSID;
String _userPASS;

void serverConfiguration::init(){

    localServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){

        request->send(SPIFFS, "/index.html", "text/html");
    });

    localServer.on("/formoid-solid-green.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/formoid-solid-green.css", "text/css");
    });

    localServer.on("/apinit", HTTP_GET, [](AsyncWebServerRequest *request){
 
        int paramsNr = request->params();
 
        for(int i=0;i<paramsNr;i++){
 
            AsyncWebParameter* p = request->getParam(i);

            if(p->name() == "userSSID"){

                _userSSID = p->value();
            }
            else if(p->name() == "userPASS"){

                _userPASS = p->value();
            }
        }

        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();

        json["ssid"] = _userSSID;
        json["pass"] = _userPASS;

        File configFile = SPIFFS.open("/config.json", "w");

        if (!configFile) {
            Serial.println("failed to open config file for writing");
        }

        json.prettyPrintTo(Serial);
        json.printTo(configFile);

        configFile.close();
 
        request->send(200, "text/plain", "Device restarting...");

        delay(2000);

        ESP.restart();
        });

    localServer.begin();
}

void serverConfiguration::handleClient(){
}

