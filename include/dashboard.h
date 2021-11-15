#ifndef ARDUINO_FOG_DASHBOARD_H
#define ARDUINO_FOG_DASHBOARD_H

#include <Arduino.h>
#include "fogger.h"

/* ESP8266 Dependencies */
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>
#include <ESPAsyncE131.h>

extern int timer_card_value;
extern int duration_card_value;
extern bool stop_smoke_card_value;
extern bool auto_smoke_card_value;
extern bool force_smoke_card_value;
extern String current_state_card_value;
extern String e131_card_value;

void dashboard_setup();
void dashboard_loop();

void attach_callbacks();

#endif //ARDUINO_FOG_DASHBOARD_H
