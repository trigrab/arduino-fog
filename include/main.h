#ifndef ARDUINO_FOG_MAIN_H
#define ARDUINO_FOG_MAIN_H

#include <Arduino.h>

#include "wifi.h"
#include "ota.h"
//#include "dashboard.h"
#include "fogger.h"
#include "e131.h"
#include "webUI.h"

// fogger values
unsigned long _watch, _seconds;
unsigned int _duration;
int _nextTimer;
uint8_t _currentState;
bool _first;
uint8_t _smokeDuration;
uint8_t _pauseDuration;
WebUI webUI;

// dashboard values
int timer_card_value;
int duration_card_value;
bool stop_smoke_card_value;
bool auto_smoke_card_value;
bool force_smoke_card_value;
String current_state_card_value;
String e131_card_value;

void setup();
void loop();

#endif // ARDUINO_FOG_MAIN_H
