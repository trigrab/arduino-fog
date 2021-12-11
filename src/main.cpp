#include "main.h"

void setup() {
  Serial.begin(115200);
  webUI = WebUI();
  fogger = Fogger();
  e131 = E131();

  wifi_setup();
  ota_setup();
  //dashboard_setup();
  fogger.setup();
  e131.setup();
  webUI.setup();
}

void loop() {
  ota_loop();
  //dashboard_loop();
  fogger.loop();
  e131.loop();
  webUI.loop();
}
