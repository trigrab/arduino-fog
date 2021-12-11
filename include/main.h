#ifndef ARDUINO_FOG_MAIN_H
#define ARDUINO_FOG_MAIN_H

#include <Arduino.h>

#include "wifi.h"
#include "ota.h"
//#include "dashboard.h"
#include "fogger.h"
#include "e131.h"
#include "webUI.h"

Fogger fogger;
WebUI webUI;
E131 e131;

// dashboard values
int timer_card_value;
int duration_card_value;
bool stop_smoke_card_value;
bool auto_smoke_card_value;
bool force_smoke_card_value;

void setup();
void loop();

#endif // ARDUINO_FOG_MAIN_H
