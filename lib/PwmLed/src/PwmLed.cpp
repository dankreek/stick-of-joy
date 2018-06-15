#include <Arduino.h>
#include <cstdint>
#include "PwmLed.hpp"

namespace dankreek {

  void PwmLed::init() {
    analogWriteResolution(ANALOG_WRITE_RESOLUTION);
  }

  void PwmLed::initInstance(uint8_t pin) {
    this->_pinNum = pin;
    this->setBrightness(0);
  }

  PwmLed::PwmLed(uint8_t pinNum, float frequency) {
    analogWriteFrequency(pinNum, frequency);
    this->initInstance(pinNum);
  }

  PwmLed::PwmLed(uint8_t pinNum) {
    // TODO: Manually set the default frequency when a reasonable value is found
    this->initInstance(pinNum);
  }

  void PwmLed::setBrightness(uint16_t brightness) {
    this->_brightness = brightness;
    analogWrite(this->_pinNum, brightness);
  }

  uint16_t PwmLed::getBrightness() {
    return this->_brightness;
  }
}
