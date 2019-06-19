#include <hardware.h>

hardwareConfiguration hardware;

uint8_t hardwareStatusBitMask = 0x00;

void hardwareConfiguration::init(){

    //Init GPIO
    pinMode(LED_BUILTIN, OUTPUT);

    //Serial configuration
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); //Clears some space
    
    //SPIFFS Init
    if(!SPIFFS.begin(true)){

        //SPIFFS Failed
        hardwareStatusBitMask = hardwareStatusBitMask | 0x01;
        return;
    }


}

void hardwareConfiguration::printStatus(){

    printf("=================================================\n");
    printf("\tESP32 SmartControl\n");
    printf("\tDeveloped by Ivan - ivanplozancic@gmail.com\n");
    printf("=================================================\n");
    printf("\tHardware Check\n");
    printf("\tSerial baud rate: %i\n", SERIAL_BAUD_RATE);
    printf("\tSPIFFS status: %s\n", (hardwareStatusBitMask & 0x01) ? "ERROR" : "OK");
    printf("=================================================\n");
}