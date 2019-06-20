/****************************************************************************
 *  @module:    ringDisplay.cpp
 *  @brief:     Source code for controlling homl.io master device ring 
 *              display
 * 
 *  @author:    Ivan Pavao Lozančić
 *  @date:      06/19/2019      
 ****************************************************************************/

#include <ringDisplay.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(RINGDISP_NUM, RINGDISP_PIN, NEO_GRB + NEO_KHZ800);

bool fetchDispData(){

}

void ringDisp_init(){

    //Ring display
    pixels.begin();
}

void ringDisp_turnOnAll(uint32_t COLOR){

    uint8_t COUNTER;        //Pixel counter
    uint8_t COLOR_RED;      //Variable for red LED
    uint8_t COLOR_GREEN;    //Variable for green LED
    uint8_t COLOR_BLUE;     //Variable for blue LED

    COLOR_RED = COLOR >> 16 & 0xFF;     //Get red color from desired color
    COLOR_GREEN = COLOR >> 8 & 0xFF;    //Get green color from desired color
    COLOR_BLUE = COLOR & 0xFF;          //Get blue color from desired color

    //Set all pixels to desired colour
    for(COUNTER = 0; COUNTER < RINGDISP_NUM; COUNTER++){
        pixels.setPixelColor(COUNTER, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));
    }

    //Update display
    pixels.show();
}

void ringDisp_turnOffAll(){

    uint8_t COUNTER;    //Pixel counter

    //Set all pixels to low -> RED, GREEN, BLUE = 0
    for(COUNTER = 0; COUNTER < RINGDISP_NUM; COUNTER++){
        pixels.setPixelColor(COUNTER, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, RINGDISP_TURNOFF));
    }

    //Update display
    pixels.show();
}

void ringDisp_pixelFadeTest(uint8_t pixel, uint8_t time){

    uint8_t COUNTER;

    //RED
    for(COUNTER = 0; COUNTER < 0xFF; COUNTER++){
        pixels.setPixelColor(pixel, pixels.Color(COUNTER, RINGDISP_TURNOFF, RINGDISP_TURNOFF));
        pixels.show();
        delay(time);
    }

    //GREEN
    for(COUNTER = 0; COUNTER < 0xFF; COUNTER++){
        pixels.setPixelColor(pixel, pixels.Color(RINGDISP_TURNOFF, COUNTER, RINGDISP_TURNOFF));
        pixels.show();
        delay(time);
    }

    //BLUE
    for(COUNTER = 0; COUNTER < 0xFF; COUNTER++){
        pixels.setPixelColor(pixel, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, COUNTER));
        pixels.show();
        delay(time);
    }

    //WHITE
    for(COUNTER = 0; COUNTER < 0xFF; COUNTER++){
        pixels.setPixelColor(pixel, pixels.Color(COUNTER, COUNTER, COUNTER));
        pixels.show();
        delay(time);
    }
    
}

void ringDisp_ringColorTest(){
    ringDisp_turnOnAll(RINGDISP_RED);
    delay(RINGDISP_TESTTIME);
    ringDisp_turnOnAll(RINGDISP_GREEN);
    delay(RINGDISP_TESTTIME);
    ringDisp_turnOnAll(RINGDISP_BLUE);
    delay(RINGDISP_TESTTIME);
    ringDisp_turnOnAll(RINGDISP_WHITE);
    delay(RINGDISP_TESTTIME);
    ringDisp_turnOffAll();
}

void ringDisp_cwRun(uint32_t COLOR){

    uint8_t COUNTER;        //Pixel counter
    uint8_t COLOR_RED;      //Variable for red LED
    uint8_t COLOR_GREEN;    //Variable for green LED
    uint8_t COLOR_BLUE;     //Variable for blue LED

    COLOR_RED = COLOR >> 16 & 0xFF;     //Get red color from desired color
    COLOR_GREEN = COLOR >> 8 & 0xFF;    //Get green color from desired color
    COLOR_BLUE = COLOR & 0xFF;          //Get blue color from desired color

    for(COUNTER = 0; COUNTER < RINGDISP_NUM; COUNTER++){

        pixels.setPixelColor(COUNTER, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE)); //Set current pixel to desired state
        pixels.setPixelColor(COUNTER - 1, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, RINGDISP_TURNOFF)); //Set current pixel to desired state

        pixels.show();

        delay(30);
    }

    //Turn off the last pixel
    pixels.setPixelColor(0xF, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, RINGDISP_TURNOFF));

    pixels.show();
}

void ringDisp_ccwRun(uint32_t COLOR){

    uint8_t COUNTER;        //Pixel Counter
    uint8_t COLOR_RED;      //Variable for red LED
    uint8_t COLOR_GREEN;    //Variable for green LED
    uint8_t COLOR_BLUE;     //Variable for blue LED

    COLOR_RED = COLOR >> 16 & 0xFF;     //Get red color from desired color
    COLOR_GREEN = COLOR >> 8 & 0xFF;    //Get green color from desired color
    COLOR_BLUE = COLOR & 0xFF;          //Get blue color from desired color

    for(COUNTER = 15; COUNTER == 0; COUNTER--){

        //Set current pixel to desired state
        pixels.setPixelColor(COUNTER, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE)); 
        //Set current pixel to desired state
        pixels.setPixelColor(COUNTER + 1, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, RINGDISP_TURNOFF)); 

        //Update ring display
        pixels.show();

        delay(30);
    }

    pixels.setPixelColor(0, pixels.Color(RINGDISP_TURNOFF, RINGDISP_TURNOFF, RINGDISP_TURNOFF));

    pixels.show();
}

void ringDisp_showPercentage(uint8_t percentage, uint32_t COLOR){

    uint8_t COUNTER;            //Pixel Counter
    uint8_t COLOR_RED;          //Variable for red LED
    uint8_t COLOR_GREEN;        //Variable for green LED
    uint8_t COLOR_BLUE;         //Variable for blue LED
    uint8_t RINGDISP_NUMBER;    //Variable for how many pixels need to be turned on

    COLOR_RED = COLOR >> 16 & 0xFF;     //Get red color from desired color
    COLOR_GREEN = COLOR >> 8 & 0xFF;    //Get green color from desired color
    COLOR_BLUE = COLOR & 0xFF;          //Get blue color from desired color
    RINGDISP_NUMBER = percentage / 6;   //Calculate how many pixels need to be turned on

    for(COUNTER = 0; COUNTER < RINGDISP_NUM; COUNTER++){
       pixels.setPixelColor(COUNTER, pixels.Color(COLOR_RED, COLOR_GREEN, COLOR_BLUE));  
    }

    pixels.show();
}