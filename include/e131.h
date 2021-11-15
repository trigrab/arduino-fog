#ifndef ARDUINO_FOG_E131_H
#define ARDUINO_FOG_E131_H

#include <ESPAsyncE131.h>

#include "fogger.h"

#define UNIVERSE 1                      // First DMX Universe to listen for
#define UNIVERSE_COUNT 2                // Total number of Universes to listen for, starting at UNIVERSE

void e131_setup();
void e131_loop();

#endif // ARDUINO_FOG_E131_H
