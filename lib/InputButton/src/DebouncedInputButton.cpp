#include <Arduino.h>
#include <Bounce2.h>
#include "DebouncedInputButton.hpp"

namespace dankreek {

DebouncedInputButton::DebouncedInputButton(
  uint8_t pin,
  unsigned long intervalMS
) {
  this->_debouncer.attach(pin, INPUT_PULLUP);
  this->_debouncer.interval(intervalMS);
}

bool DebouncedInputButton::update() {
  return this->_debouncer.update();
}

bool DebouncedInputButton::read() {
  return this->_debouncer.read();
}

bool DebouncedInputButton::fell() {
  return this->_debouncer.fell();
}

bool DebouncedInputButton::rose() {
  return this->_debouncer.rose();
}

}
