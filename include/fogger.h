#ifndef ARDUINO_FOG_FOGGER_H
#define ARDUINO_FOG_FOGGER_H

#include <Arduino.h>

/* ESP8266 Dependencies */
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

// fogger values
extern unsigned long _watch, _seconds;
extern unsigned int _duration;
extern int _nextTimer;
extern unsigned int _currentState;
extern bool _first;

// dashboard values
extern int timer_card_value;
extern int duration_card_value;
extern bool stop_smoke_card_value;
extern bool auto_smoke_card_value;
extern bool force_smoke_card_value;
extern String current_state_card_value;
extern String e131_card_value;

#define DURATION 30 // time in seconds where smoke is on
#define PAUSE 120 // Pause between smoke in seconds
#define WARMUP 10 // time in seconds before first smoke
#define SMOKE_PIN 1
#define PAUSE_STATE 0
#define SMOKE_STATE 1
#define STOP_STATE 2
#define WARMUP_STATE 3
#define HOLD_STATE 4
#define START_STATE 3
#define LED_PIN 4

void fogger_setup();
void fogger_loop();

void handleE131();
void printHelp();
void printParameters();
void printState();
void printStateHelper(String message);
void changeState();
unsigned int getRemainingSeconds();
void startTimer(unsigned int durationInSeconds);
bool checkTimer();
void stop();
void setState(uint8_t state);

#endif //ARDUINO_FOG_FOGGER_H
