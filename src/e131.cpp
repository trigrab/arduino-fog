#include "e131.h"

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);

void e131_setup() {
    if (e131.begin(E131_UNICAST)) {
      Serial.println(F("Listening for e1.31 data..."));
    }
    else {
      Serial.println(F("*** e1.31.begin failed ***"));
    }
}

void e131_loop() {
  if (!e131.isEmpty()) {
    e131_packet_t packet;
    e131.pull(&packet);     // Pull packet from ring buffer
    unsigned int brightness = packet.property_values[1];
    if (brightness > 127) {
      setState(HOLD_STATE);
      e131_card_value = "Force";
    }
    else {
      setState(STOP_STATE);
      e131_card_value = "Stop";
    }
  }
}
