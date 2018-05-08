#include <Arduino.h>
#include "Pot.hpp"

namespace dankreek {

  void Pot::init() {
    analogReadResolution(ANALOG_READ_RESOLUTION);
    analogReadAveraging(ANALOG_READ_AVERAGING_NUM_SAMPLES);
  }

  Pot::Pot(uint8_t potPin) {
    this->_potPin = potPin;
    _curValue = analogRead(this->_potPin);
    _lastValue = _curValue;
  }


  bool Pot::update() {
    _lastValue = _curValue;
    _curValue = analogRead(this->_potPin);
    return _lastValue != _curValue;
  }

  int Pot::read() {
    return this->_curValue;
  }
}
