#include "wifi.h"

void wifi_setup() {
#ifdef WIFI_SSID
#ifdef WIFI_PASS
    WiFi.begin(WIFI_SSID, WIFI_PASS);
#endif // WIFI_PASS
#endif // WIFI_SSID

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
}
