#include <Arduino.h>
#include <cstdint>
#include "PwmLed.hpp"

namespace dankreek {

  void PwmLed::init() {
    analogWriteResolution(ANALOG_WRITE_RESOLUTION);
  }

  PwmLed::PwmLed(uint8_t pinNum, ledBrightness maxBrightness) {
    this->_pinNum = pinNum;
    this->_maxBrightness = maxBrightness;
    this->hardOff();
  }

  void PwmLed::hardOff() {
    this->setBrightness(0);
    this->stopTransition();
  }

  void PwmLed::hardOn() {
    this->setBrightness(this->_maxBrightness);
    this->stopTransition();
  }

  void PwmLed::softOn(uint16_t transitionTimeMs) {
    this->startTransition(transitionTimeMs, true);
  }

  void PwmLed::softOff(uint16_t transitionTimeMs) {
    this->startTransition(transitionTimeMs, false);
  }

  void PwmLed::setBrightness(ledBrightness brightness) {
    this->_curBrightness = brightness;
    analogWrite(this->_pinNum, brightness);
  }

  void PwmLed::startTransition(uint16_t transitionTimeMs, bool isIncreasing) {
    this->_timeSinceLastStep = 0;
    this->_isTransitionIncreasing = isIncreasing;

    this->_nextStepTime_us =
      (unsigned long)(1000) * (unsigned long)(transitionTimeMs) / (unsigned long)(this->_maxBrightness);
  }

  void PwmLed::stopTransition() {
    this->_nextStepTime_us = 0;
  }

  bool PwmLed::isTransitionRunning() {
    return (this->_nextStepTime_us > 0);
  }

  bool PwmLed::isNextStepTime() {
    return (this->_timeSinceLastStep >= this->_nextStepTime_us);
  }

  void PwmLed::update() {
    if (this->isTransitionRunning() && this->isNextStepTime()) {
      // If the brightness is at the max or min, the transition is over.
      if (((this->_curBrightness == 0) && !this->_isTransitionIncreasing) ||
          ((this->_curBrightness == this->_maxBrightness) && this->_isTransitionIncreasing))
      {
        this->stopTransition();
      }
      else {
        this->setBrightness(
          this->_curBrightness + (this->_isTransitionIncreasing ? 1 : -1)
        );
        this->_timeSinceLastStep = 0;
      }
    }
  }
}
