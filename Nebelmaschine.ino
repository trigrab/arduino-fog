unsigned long _watch, _seconds;
unsigned int _duration;
int _nextTimer;
unsigned int _currentState;


#define DURATION 10 // time in seconds where smoke is on
#define PAUSE 600 // Pause between smoke in seconds
#define WARMUP 300 // time in seconds before first smoke
#define SMOKE_PIN 9
#define PAUSE_STATE 0
#define SMOKE_STATE 1
#define STOP_STATE 2
#define WARMUP_STATE 3
#define HOLD_STATE 4

void setup() {
  pinMode(SMOKE_PIN, OUTPUT);
  digitalWrite(SMOKE_PIN, LOW);
  _watch = 0;
  _duration = 0;
  _nextTimer = WARMUP;
  _currentState = WARMUP_STATE;
  startTimer(_nextTimer);
  Serial.begin(115200);
  delayMicroseconds(10);
  Serial.print("Arduino Ready, ");
  Serial.print(_nextTimer);
  Serial.println("s till first smoke");
}

void loop() {
  if (checkTimer()) {
    if (_nextTimer > -1){
      changeState();
    }
  }
  if (Serial.available() > 0) {
                // read the incoming byte:
                String incoming = Serial.readString();

                if (incoming.startsWith("sto")) {
                  _currentState = STOP_STATE;
                  changeState();
                }
                else if (incoming.startsWith("star")) {
                  _currentState = SMOKE_STATE;
                  _watch = millis();
                  changeState();
                }
                else if (incoming.startsWith("smo")) {
                  _currentState = PAUSE_STATE;
                  _watch = millis();
                  changeState();
                }
                else if (incoming.startsWith("hol")) {
                  _currentState = HOLD_STATE;
                  _watch = millis();
                  changeState();
                }
                else if (incoming.startsWith("pau")) {
                  _currentState = SMOKE_STATE;
                  _watch = millis();
                  changeState();
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
   Serial.println("Pause duration - " + String(PAUSE) + "s");
   Serial.println("Smoke duration - " + String(DURATION) + "s");
}


void printState() {
   Serial.print("State is ");
    switch (_currentState) {
      case PAUSE_STATE: 
        Serial.println("Pause: " + String(getRemainingSeconds()) + "s");
        break;
      case SMOKE_STATE: 
        Serial.println("Smoke: " + String(getRemainingSeconds()) + "s");
        break;
      case STOP_STATE: 
        Serial.println("Stop");
        break;
      case WARMUP_STATE: 
        Serial.println("WarmUp: " + String(getRemainingSeconds()) + "s");
        break;
      case HOLD_STATE: 
        Serial.println("Hold");
        break;
      default:
        Serial.println(_currentState);
    }
}

void changeState() {
switch(_currentState) {
  case PAUSE_STATE:
    digitalWrite(SMOKE_PIN, HIGH);
    _nextTimer = DURATION;
    _currentState = SMOKE_STATE;
    break;
  case SMOKE_STATE:
    digitalWrite(SMOKE_PIN, LOW);
    _nextTimer = PAUSE;
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
  }
  startTimer(_nextTimer);
  printState();
}

unsigned int getRemainingSeconds() {
  return _duration - ((millis() - _watch) / 1000);
}

void startTimer(unsigned int durationInSeconds ) {
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

