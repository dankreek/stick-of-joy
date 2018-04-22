#include <Arduino.h>
#include <cstdint>
#include "PwmLed.hpp"

namespace dankreek {



  void PwmLed::init() {
    analogWriteResolution(ANALOG_WRITE_RESOLUTION);
  }

  void PwmLed::initInstance(uint8_t pin) {
    this->_pinNum = pin;
    this->_mode = stopped;
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

  void PwmLed::constant(uint16_t brightness) {
    this->_mode = stopped;
    this->setBrightness(brightness);
  }

  void PwmLed::startGradient(
    uint16_t initBrightness,
    uint16_t finalBrightness,
    uint16_t timeMS
  ) {
    this->_timer = 0;
    this->_startBrightness = initBrightness;
    this->_endBrightness = finalBrightness;
    this->_animTimeUs = timeMS * 1000;
    this->_mode = gradient;
    this->_changeRate = double(finalBrightness - initBrightness) / double(this->_animTimeUs);
    this->setBrightness(initBrightness);
  }

  void PwmLed::handleGradientChange() {
      // The gradient is over
      if (this->_timer >= this->_animTimeUs) {
        this->setBrightness(this->_endBrightness);
        this->_mode = stopped;
      }
      // Calculate the current brightness
      else {
        this->setBrightness(
          double(this->_timer) *
          this->_changeRate +
          this->_startBrightness
        );
      }
  }

  void PwmLed::update() {
    switch (this->_mode) {
      case stopped: break;
      case gradient: this->handleGradientChange(); break;
      case oscillating: this->handleOscillateChange(); break;
    }
  }
}
