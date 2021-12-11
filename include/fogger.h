#ifndef ARDUINO_FOG_FOGGER_H
#define ARDUINO_FOG_FOGGER_H

#include <Arduino.h>

#define SMOKE_DURATION 30 // time in seconds where smoke is on
#define PAUSE_DURATION 120 // Pause between smoke in seconds
#define WARMUP 10 // time in seconds before first smoke
#define SMOKE_PIN 1
#define PAUSE_STATE 0
#define SMOKE_STATE 1
#define STOP_STATE 2
#define WARMUP_STATE 3
#define HOLD_STATE 4
#define START_STATE 3
#define LED_PIN 4

class Fogger {
  private:
    unsigned long _watch, _seconds;
    unsigned int _duration;
    int _nextTimer;
    uint8_t _currentState;
    bool _first;
    uint8_t _smokeDuration;
    uint8_t _pauseDuration;

    void handleSerial();
    void handleE131();
    void printHelp();
    void printParameters();
    void printState();
    void printStateHelper(String message);

  public:
    String currentState;

    Fogger();
    void setup();
    void loop();
    void changeState();
    unsigned int getRemainingSeconds();
    void startTimer(unsigned int durationInSeconds);
    bool checkTimer();
    void stop();
    void setState(uint8_t state);
    uint8_t getState();
    void setSmokeDuration(uint8_t duration);
    uint8_t getSmokeDuration();
    void setPauseDuration(uint8_t duration);
    uint8_t getPauseDuration();
};


#endif //ARDUINO_FOG_FOGGER_H
