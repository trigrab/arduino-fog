#include "webUI.h"

WebUI::WebUI() {

}

void WebUI::setup() {
  _controlsTab = ESPUI.addControl( ControlType::Tab, "Controls", "Controls" );
  _settingsTab = ESPUI.addControl( ControlType::Tab, "Settings", "Settings" );

  // shown above all tabs

  _status_label = ESPUI.addControl( ControlType::Label, "Status:", fogger.currentState, ControlColor::None );
  _timer_label = ESPUI.addControl( ControlType::Label, "Timer:", (String) fogger.getRemainingSeconds() + " s", ControlColor::None );
  _e131_label = ESPUI.addControl( ControlType::Label, "E131 status:", e131.state, ControlColor::None );
  _smoke_duration_input = ESPUI.addControl(ControlType::Number, "Smoke duration (in s)", (String) fogger.getSmokeDuration(), ControlColor::Carrot, _settingsTab, &_setSmokeDuration);
  _pause_duration_input = ESPUI.addControl(ControlType::Number, "Pause duration (in s)", (String) fogger.getPauseDuration(), ControlColor::Carrot, _settingsTab, &_setPauseDuration);
  _force_smoke_button = ESPUI.addControl(ControlType::Button, "Force Smoke", "Smoke", ControlColor::Peterriver, _controlsTab, &_forceSmoke);
  _stop_smoke_button = ESPUI.addControl(ControlType::Button, "Stop Smoke", "Stop", ControlColor::Peterriver, _controlsTab, &_stopSmoke);
  _auto_smoke_button = ESPUI.addControl(ControlType::Button, "Auto Smoke", "Auto Mode", ControlColor::Peterriver, _controlsTab, &_autoMode);
  _smoke_button = ESPUI.addControl(ControlType::Button, "Push to Smoke", "Smoke", ControlColor::Peterriver, _controlsTab, &_smoke);
  ESPUI.begin("Arduino Fog");
}

void WebUI::loop() {
  updateControlIfChanged(_status_label, fogger.currentState);
  updateControlIfChanged(_timer_label, (String) fogger.getRemainingSeconds() + "s");
  updateControlIfChanged(_e131_label, e131.state);
}

void WebUI::updateControlIfChanged(uint8_t control, String value) {
  if (value != ESPUI.getControl(control)->value) {
    ESPUI.updateControlValue(control, value);
  }
}

void WebUI::_setSmokeDuration(Control *sender, int type) {
  uint8_t value = sender->value.toInt();
  fogger.setSmokeDuration(value);
}

void WebUI::_setPauseDuration(Control *sender, int type) {
  uint8_t value = sender->value.toInt();
  fogger.setPauseDuration(value);
}

void WebUI::_stopSmoke(Control *sender, int type) {
  fogger.setState(STOP_STATE);
}

void WebUI::_autoMode(Control *sender, int type) {
  fogger.setState(PAUSE_STATE);
}

void WebUI::_forceSmoke(Control *sender, int type) {
  fogger.setState(HOLD_STATE);
}

void WebUI::_smoke(Control *sender, int type) {
  switch (type) {
  case B_DOWN:
    webUI.lastState = fogger.getState();
    fogger.setState(SMOKE_STATE);
    break;

  case B_UP:
    fogger.setState(webUI.lastState);
    break;
  }
    
}