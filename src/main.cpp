#include <main.h>
#include <hardware.h>
#include <wifiInit.h>
#include <serverInit.h>
#include <ringDisplay.h>

void setup() {

  hardware.init();

  hardware.printStatus();

  wifi.init();

  wifi.printStatus();

  ringDisp_turnOffAll(); 

  ringDisp_cwRun(RINGDISP_GREEN);
  ringDisp_ccwRun(RINGDISP_GREEN);
}

void loop() {
  
  
}