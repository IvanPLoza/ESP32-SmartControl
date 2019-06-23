#include <serverInit.h>

AsyncWebServer localServer(80);
WiFiClient localClient;

serverConfiguration server;

String _userSSID;
String _userPASS;

bool loggedIn = false;

void serverConfiguration::init(){

    localServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){

        request->send(SPIFFS, "/index.html", "text/html");
    });

    localServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css");
    });

    localServer.on("/dashboard", HTTP_GET, [](AsyncWebServerRequest *request){

        if(loggedIn == true){

            request->send(SPIFFS, "/dashboard/index.html", "text/html");
        }
        else{

            request->send(200, "text/plain", "You are not loged in...");
        }
    });

    localServer.on("/login", HTTP_GET, [](AsyncWebServerRequest *request){
 
        AsyncWebParameter* loginP = request->getParam(0);

        if(loginP->name() == "login-username" && loginP->value() == DEVICE_USERNAME){
                
            loginP = request->getParam(1);

            if(loginP->name() == "login-password" && loginP->value() == DEVICE_PASSWORD){

                loggedIn = true;

                request->redirect("/dashboard");
            }
            else {

                request->send(200, "text/plain", "You typed in wrong password.");

                delay(3000);

                request->redirect("/");
            }
        }
        else{

            request->send(200, "text/plain", "Incorrect username and password.");

            delay(3000);

            request->redirect("/");
        }
            
    });

    localServer.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){

        loggedIn = false;

        request->redirect("/");
    });

    localServer.on("/ap-init", HTTP_GET, [](AsyncWebServerRequest *request){
 
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

    localServer.on("/listSSID", HTTP_GET, [](AsyncWebServerRequest *request){

        StaticJsonBuffer<200> jsonBuffer;
        JsonArray& array1 = jsonBuffer.createArray();

        int n = WiFi.scanNetworks();

        String requestBuffer;

        if (n == 0) {
            request->send(200, "text/plane", "");
        } 
        else {
            for (int i = 0; i < n; ++i) {
        
                array1.add(WiFi.SSID(i));
            }

            array1.printTo(requestBuffer);
        }

        request->send(200, "text/plane", requestBuffer);
    });

    localServer.begin();
}

void serverConfiguration::handleClient(){
}

