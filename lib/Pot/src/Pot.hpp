#ifndef POT_H
#define POT_H

#include <cstdint>

namespace dankreek {

class Pot {
public:
  static const unsigned int ANALOG_READ_RESOLUTION = 16;
  static const unsigned int ANALOG_READ_AVERAGING_NUM_SAMPLES = 32;

  // Initialize the Teensy's analog input functionality
  static void init();

  Pot(uint8_t potPin);

  // Read the current value of the pot and return `true` if the value has
  // changed since the last update.
  bool update();

  // Read the current value of the potentiometer
  // Returns a value between 0 and 2^ANALOG_READ_RESOLUTION
  int read();

protected:
  uint8_t _potPin;
  int _lastValue;
  int _curValue;
};

}

#endif
