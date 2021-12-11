#include "fogger.h"

void fogger_setup() {
  pinMode(SMOKE_PIN, OUTPUT);
  digitalWrite(SMOKE_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  _first = true;
  _watch = 0;
  _duration = 0;
  _nextTimer = WARMUP;
  _currentState = START_STATE;
  _smokeDuration = SMOKE_DURATION;
  _pauseDuration = PAUSE_DURATION;
  startTimer(_nextTimer);
}

void fogger_loop() {
  if (_first) {
    Serial.print("Arduino Ready, ");
    Serial.print(_nextTimer);
    Serial.println("s till first smoke");
    _first = false;
  }
  if (checkTimer()) {
    if (_nextTimer > -1){
      changeState();
    }
  }

  duration_card_value = (int) _duration;
  timer_card_value = (int) getRemainingSeconds();

  if (Serial.available() > 0) {
                // read the incoming byte:
                String incoming = Serial.readString();

                if (incoming.startsWith("sto")) {
                  setState(STOP_STATE);
                }
                else if (incoming.startsWith("star")) {
                  setState(SMOKE_STATE);
                }
                else if (incoming.startsWith("smo")) {
                  setState(PAUSE_STATE);
                }
                else if (incoming.startsWith("hol")) {
                  setState(HOLD_STATE);
                }
                else if (incoming.startsWith("pau")) {
                  setState(SMOKE_STATE);
                }
                else if (incoming.startsWith("par")) {
                  printParameters();
                }
                else if (incoming.startsWith("stat")) {
                  printState();
                }
                else {
                  Serial.println();
                  if (!incoming.startsWith("hel")) {
                    incoming.trim();
                    Serial.println(incoming + " not recognized");
                  }
                  printHelp();
                }
  }
}

void printHelp() {
  printState();
  Serial.println("All commands are only checked with prefixes");
  Serial.println("Possible commands are:");
  Serial.println("help - print this help message");
  Serial.println("start - start normal mode with pause");
  Serial.println("stop - stop smoking");
  Serial.println("hold - smoke for infinity");
  Serial.println("smoke - change to smoke state");
  Serial.println("pause - change to pause state");
  Serial.println("state - print current state");
  Serial.println("parameters - print static parameters");
}

void printParameters() {
   Serial.println("static parameters are: ");
   Serial.println("Pin for smoke maker - " + String(SMOKE_PIN) + "s");
   Serial.println("Warmup duration - " + String(WARMUP) + "s");
   Serial.println("Pause duration - " + String(_pauseDuration) + "s");
   Serial.println("Smoke duration - " + String(_smokeDuration) + "s");
}


void printState() {
  Serial.print("State is ");
  switch (_currentState) {
    case PAUSE_STATE:
      printStateHelper("Pause: " + String(getRemainingSeconds()) + "s");
      break;
    case SMOKE_STATE:
      printStateHelper("Smoke: " + String(getRemainingSeconds()) + "s");
      break;
    case STOP_STATE:
      printStateHelper("Stop");
      break;
    case WARMUP_STATE:
      printStateHelper("WarmUp: " + String(getRemainingSeconds()) + "s");
      break;
    case HOLD_STATE:
      printStateHelper("Hold");
      break;
    default:
      Serial.println(_currentState);
  }
}

void printStateHelper(String message) {
  current_state_card_value = message;
  Serial.println(current_state_card_value);
}

void changeState() {
  auto_smoke_card_value = false;
  stop_smoke_card_value = false;
  force_smoke_card_value = false;
  switch(_currentState) {
    case PAUSE_STATE:
      digitalWrite(SMOKE_PIN, HIGH);
      _nextTimer = _smokeDuration;
      _currentState = SMOKE_STATE;
      auto_smoke_card_value = true;
      break;
    case SMOKE_STATE:
      digitalWrite(SMOKE_PIN, LOW);
      _nextTimer = _pauseDuration;
      _currentState = PAUSE_STATE;
      auto_smoke_card_value = true;
      break;
    case HOLD_STATE:
      digitalWrite(SMOKE_PIN, HIGH);
      _nextTimer = -1;
      force_smoke_card_value = true;
      break;
    case STOP_STATE:
      digitalWrite(SMOKE_PIN, LOW);
      _nextTimer = -1;
      stop_smoke_card_value = true;
      break;
    case WARMUP_STATE:
      _nextTimer = _smokeDuration;
      digitalWrite(SMOKE_PIN, HIGH);
      _currentState = SMOKE_STATE;
      auto_smoke_card_value = true;
      break;
  }
  e131_card_value = "Off";
  startTimer(_nextTimer);
  printState();
}

unsigned int getRemainingSeconds() {
  if (_nextTimer < 0) {
    return 0;
  }
  return _duration - ((millis() - _watch) / 1000);
}

void startTimer(unsigned int durationInSeconds) {
  _watch = millis();
  _duration = durationInSeconds;
}

bool checkTimer() {
  if (getRemainingSeconds() > _duration) {
    return true;
  }
  else {
    return false;
  }
}

void stop() {
   _currentState = STOP_STATE;
}

void setState(uint8_t state) {
  _currentState = state;
  changeState();
}

uint8_t getState() {
  return _currentState;
}

void setSmokeDuration(uint8_t duration) {
  _smokeDuration = duration;
}

uint8_t getSmokeDuration() {
  return _smokeDuration;
}

void setPauseDuration(uint8_t duration) {
  _pauseDuration = duration;
}

uint8_t getPauseDuration() {
  return _pauseDuration;
}