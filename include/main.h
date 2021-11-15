#ifndef ARDUINO_FOG_MAIN_H
#define ARDUINO_FOG_MAIN_H

#include <Arduino.h>

#include "wifi.h"
#include "ota.h"
#include "dashboard.h"
#include "fogger.h"
#include "e131.h"

// fogger values
unsigned long _watch, _seconds;
unsigned int _duration;
int _nextTimer;
unsigned int _currentState;
bool _first;

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
