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

  server.init();
}

void loop() {
  
  
}