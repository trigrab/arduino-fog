#ifndef ARDUINO_FOG_WEBUI_H
#define ARDUINO_FOG_WEBUI_H

#include <ESPUI.h>
#include "fogger.h"
#include "e131.h"

extern String current_state_card_value;
extern Fogger fogger;
extern E131 e131;

class WebUI {
  private:
    uint16_t _controlsTab;
    uint16_t _settingsTab;
    uint16_t _status_label;
    uint16_t _timer_label;
    uint16_t _e131_label;
    uint16_t _smoke_duration_input;
    uint16_t _pause_duration_input;
    uint16_t _force_smoke_button;
    uint16_t _auto_smoke_button;
    uint16_t _stop_smoke_button;
    uint16_t _smoke_button;

    static void _setSmokeDuration(Control *sender, int type);
    static void _setPauseDuration(Control *sender, int type);
    static void _forceSmoke(Control *sender, int type);
    static void _autoMode(Control *sender, int type);
    static void _stopSmoke(Control *sender, int type);
    static void _smoke(Control *sender, int type);

    static void updateControlIfChanged(uint8_t control, String value);
  
  public:
    uint16_t lastState;
    WebUI();
    void setup();
    void loop();
};

extern WebUI webUI;

#endif // ARDUINO_FOG_WEBUI_H