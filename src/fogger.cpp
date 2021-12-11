#include "fogger.h"

Fogger::Fogger() {
  _first = true;
  _watch = 0;
  _duration = 0;
  _nextTimer = WARMUP;
  _currentState = START_STATE;
  _smokeDuration = SMOKE_DURATION;
  _pauseDuration = PAUSE_DURATION;
}

void Fogger::setup() {
  pinMode(SMOKE_PIN, OUTPUT);
  digitalWrite(SMOKE_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  startTimer(_nextTimer);
}

void Fogger::loop() {
  if (_first) {
    Serial.print("Arduino Ready, ");
    printState();
    _first = false;
  }
  if (checkTimer()) {
    if (_nextTimer > -1){
      changeState();
    }
  }

  handleSerial();
}

void Fogger::handleSerial() {
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

void Fogger::printHelp() {
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

void Fogger::printParameters() {
   Serial.println("static parameters are: ");
   Serial.println("Pin for smoke maker - " + String(SMOKE_PIN) + "s");
   Serial.println("Warmup duration - " + String(WARMUP) + "s");
   Serial.println("Pause duration - " + String(_pauseDuration) + "s");
   Serial.println("Smoke duration - " + String(_smokeDuration) + "s");
}


void Fogger::printState() {
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

void Fogger::printStateHelper(String message) {
  currentState = message;
  Serial.println(currentState);
}

void Fogger::changeState() {
  switch(_currentState) {
    case PAUSE_STATE:
      digitalWrite(SMOKE_PIN, HIGH);
      _nextTimer = _smokeDuration;
      _currentState = SMOKE_STATE;
      break;
    case SMOKE_STATE:
      digitalWrite(SMOKE_PIN, LOW);
      _nextTimer = _pauseDuration;
      _currentState = PAUSE_STATE;
      break;
    case HOLD_STATE:
      digitalWrite(SMOKE_PIN, HIGH);
      _nextTimer = -1;
      break;
    case STOP_STATE:
      digitalWrite(SMOKE_PIN, LOW);
      _nextTimer = -1;
      break;
    case WARMUP_STATE:
      _nextTimer = _smokeDuration;
      digitalWrite(SMOKE_PIN, HIGH);
      _currentState = SMOKE_STATE;
      break;
  }
  startTimer(_nextTimer);
  printState();
}

unsigned int Fogger::getRemainingSeconds() {
  if (_nextTimer < 0) {
    return 0;
  }
  return _duration - ((millis() - _watch) / 1000);
}

void Fogger::startTimer(unsigned int durationInSeconds) {
  _watch = millis();
  _duration = durationInSeconds;
}

bool Fogger::checkTimer() {
  if (getRemainingSeconds() > _duration) {
    return true;
  }
  else {
    return false;
  }
}

void Fogger::stop() {
   _currentState = STOP_STATE;
}

void Fogger::setState(uint8_t state) {
  _currentState = state;
  changeState();
}

uint8_t Fogger::getState() {
  return _currentState;
}

void Fogger::setSmokeDuration(uint8_t duration) {
  _smokeDuration = duration;
}

uint8_t Fogger::getSmokeDuration() {
  return _smokeDuration;
}

void Fogger::setPauseDuration(uint8_t duration) {
  _pauseDuration = duration;
}

uint8_t Fogger::getPauseDuration() {
  return _pauseDuration;
}