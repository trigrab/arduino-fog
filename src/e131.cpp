#include "e131.h"

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 espAsyncE131(UNIVERSE_COUNT);

E131::E131() {

}

void E131::setup() {
    if (espAsyncE131.begin(E131_UNICAST)) {
      Serial.println(F("Listening for e1.31 data..."));
    }
    else {
      Serial.println(F("*** e1.31.begin failed ***"));
    }
    _idleTime = millis();
}

void E131::loop() {
  if (espAsyncE131.isEmpty()) {
    if ((millis() - _idleTime) > 1000 ) { // if more than 1s of idle time
      state = "off";
    }
  }
  else {  
    e131_packet_t packet;
    _idleTime = millis();
    espAsyncE131.pull(&packet);     // Pull packet from ring buffer
    unsigned int brightness = packet.property_values[1];
    if (brightness > 127) {
      fogger.setState(HOLD_STATE);
      state = "Force";
    }
    else {
      fogger.setState(STOP_STATE);
      state = "Stop";
    }
  }
}
