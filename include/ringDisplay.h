/****************************************************************************
 *  @module:    ringDisplay.h
 *  @brief:     Header file for ring display source code
 * 
 *  @author:    Ivan Pavao Lozančić - ivan@homl.io
 *  @date:      03/23/2019      
 ****************************************************************************/
#include <main.h>
#include <Adafruit_NeoPixel.h>

/**********************************
//RING DISPLAY CONFIGURATION
**********************************/
//GPIO - 15
#define RINGDISP_PIN        0x0F   
//Number of LEDs - 16
#define RINGDISP_NUM        0x10
//TURNOFF COLOR 
#define RINGDISP_TURNOFF    0x00
//RING TEST TIME - 500ms
#define RINGDISP_TESTTIME   0x1F4
//RING_COLOR_WHITE
#define RINGDISP_WHITE      0xFFFFFF
//RING_COLOR_RED
#define RINGDISP_RED        0xFF0000
//RING_COLOR_GREEN
#define RINGDISP_GREEN      0xFF00
//RING_COLOR_BLUE
#define RINGDISP_BLUE       0xFF

bool fetchDispData();
void ringDisp_init();

void ringDisp_turnOffAll();
void ringDisp_turnOnAll(uint32_t COLOR);

#ifdef HARDWARE_TEST
void ringDisp_pixelFadeTest(uint8_t pixel, uint8_t delay);
void ringDisp_ringColorTest();
#endif //HARDWARE_TEST

void ringDisp_cwRun(uint32_t COLOR);
void ringDisp_ccwRun(uint32_t COLOR);

void ringDisp_showPercentage(uint8_t percentage, uint32_t COLOR);

extern Adafruit_NeoPixel pixels;