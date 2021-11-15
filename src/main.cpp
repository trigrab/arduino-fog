#include "main.h"

void setup() {
  Serial.begin(115200);


  wifi_setup();
  ota_setup();
  dashboard_setup();
  fogger_setup();
  e131_setup();
}

void loop() {
  ota_loop();
  dashboard_loop();
  fogger_loop();
  e131_loop();
}
