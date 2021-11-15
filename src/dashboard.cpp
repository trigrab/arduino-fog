#include "dashboard.h"

AsyncWebServer server(80);
/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server);

Card timer(&dashboard, GENERIC_CARD, "Next State");
Card duration(&dashboard, GENERIC_CARD, "Duration");
Card stopSmoke(&dashboard, BUTTON_CARD, "Stop Smoke");
Card autoSmoke(&dashboard, BUTTON_CARD, "Auto Smoke");
Card forceSmoke(&dashboard, BUTTON_CARD, "Force Smoke");
Card currentState(&dashboard, GENERIC_CARD, "State");
Card e131Card(&dashboard, GENERIC_CARD, "E131");


void dashboard_setup() {
  attach_callbacks();
  server.begin();
  Serial.println("webserver started");
}

void dashboard_loop() {
  timer.update(timer_card_value);
  duration.update(duration_card_value);
  stopSmoke.update(stop_smoke_card_value);
  autoSmoke.update(auto_smoke_card_value);
  forceSmoke.update(force_smoke_card_value);
  currentState.update(current_state_card_value);
  e131Card.update(e131_card_value);

  dashboard.sendUpdates();
}

void attach_callbacks() {
  stopSmoke.attachCallback([&](bool value){
    Serial.println("[stopSmoke] Button Callback Triggered: "+String((value)?"true":"false"));
    setState(STOP_STATE);
    stopSmoke.update(value);
  });

  autoSmoke.attachCallback([&](bool value){
    Serial.println("[autoSmoke] Button Callback Triggered: "+String((value)?"true":"false"));
    setState(SMOKE_STATE);
    autoSmoke.update(value);
  });

  forceSmoke.attachCallback([&](bool value){
    Serial.println("[forceSmoke] Button Callback Triggered: "+String((value)?"true":"false"));
    setState(HOLD_STATE);
    forceSmoke.update(value);
    dashboard.sendUpdates();
  });
}
