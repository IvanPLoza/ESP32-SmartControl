#include <main.h>
#include <hardware.h>
#include <wifiInit.h>
#include <serverInit.h>

void setup() {

  hardware.init();

  hardware.printStatus();

  wifi.init();

  wifi.printStatus();

  server.init();
}

void loop() {
  
  
}