#include <wifiInit.h>

wifiConfiguration wifi;

uint8_t wifiStatusBitMask = 0x00;
char _wifiSSID[32];
char _wifiPASS[32];

bool wifiConfiguration::init(){
    
    if (SPIFFS.exists("/config.json")) {

        File configFile = SPIFFS.open("/config.json", "r");

        if(configFile){

            size_t size = configFile.size();

            std::unique_ptr<char[]> buf(new char[size]);

            configFile.readBytes(buf.get(), size);
            DynamicJsonBuffer jsonBuffer;
            JsonObject& json = jsonBuffer.parseObject(buf.get());

            if (json.success()) {

                if(json.containsKey("ssid")){

                    strcpy(_wifiSSID, json["ssid"]);
                    strcpy(_wifiPASS, json["pass"]);
                }
                else{

                    wifiStatusBitMask = wifiStatusBitMask | 0x01;
                }
            }
            else{

                wifiStatusBitMask = wifiStatusBitMask | 0x01;
            }
        }
        else {

            wifiStatusBitMask = wifiStatusBitMask | 0x01;
        }
    }
    else {
        
        wifiStatusBitMask = wifiStatusBitMask | 0x01;
    }

    if(wifiStatusBitMask & 0x01 == 0x01){

        WiFi.softAP(AP_SSID, AP_PASSWORD, 0);

        return false;
    }
    else{

        WiFi.begin(_wifiSSID, _wifiPASS);

        uint8_t wifiConnectTimeout = 0;

        while(WiFi.status() != WL_CONNECTED && wifiConnectTimeout < 255){

            ringDisp_showPercentage(20, RINGDISP_BLUE);
            wifiConnectTimeout++;
            delay(30);
        }

        ringDisp_turnOffAll();

        if(WiFi.status() == WL_CONNECTED){

            return true;
        }
        else {

            wifiStatusBitMask = wifiStatusBitMask | 0x01;

            WiFi.softAP(AP_SSID, AP_PASSWORD, 0);
        }
    }
}

void wifiConfiguration::printStatus(){

    printf("\tWiFi Status\n");
    printf("\tWiFi mode: \t%s\n", (wifiStatusBitMask & 0x01) ? "Access Point" : "Client");

    if((wifiStatusBitMask & 0x01) == 0x01){

        printf("\tAP SSID: \t%s\n", AP_SSID);
        printf("\tAP Password: \t%s\n", AP_PASSWORD);
        Serial.print("\tAP IP: \t");
        Serial.println(WiFi.softAPIP());   
    }
    else{

        printf("\tConnected to: \t%s\n", _wifiSSID);
        Serial.print("\tDevice IP: \t");
        Serial.println(WiFi.localIP());
    }
    printf("\t=================================================\n");
}

bool wifiConfiguration::checkConnectivity(){

    if(WiFi.status() != WL_CONNECTED){

        wifiStatusBitMask = wifiStatusBitMask | 0x01;

        WiFi.begin(_wifiSSID, _wifiPASS);

        uint8_t wifiConnectTimeout = 0;

        while(WiFi.status() != WL_CONNECTED && wifiConnectTimeout < 255){

            ringDisp_showPercentage(20, RINGDISP_BLUE);
            wifiConnectTimeout++;
            delay(30);
        }

        ringDisp_turnOffAll();

        if(WiFi.status() == WL_CONNECTED){

            wifiStatusBitMask = wifiStatusBitMask & 0xFE;
            return true;
        }
        else {

            return false;
        }
    }
}