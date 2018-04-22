#include <Arduino.h>
#include "Pot.hpp"

namespace dankreek {

  void Pot::init() {
    analogReadResolution(ANALOG_READ_RESOLUTION);
    analogReadAveraging(ANALOG_READ_AVERAGING_NUM_SAMPLES);
  }

  Pot::Pot(uint8_t potPin) {
    this->_potPin = potPin;
  }

  uint16_t Pot::value() {
    return analogRead(this->_potPin);
  }
}
