#ifndef ARDUINO_FOG_WIFI_H
#define ARDUINO_FOG_WIFI_H

#include <Arduino.h>

#if defined(ESP8266)
/* ESP8266 Dependencies */
#include <ESP8266WiFi.h>
#endif

void wifi_setup();

#endif // ARDUINO_FOG_WIFI_H
