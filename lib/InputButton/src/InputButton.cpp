#include <Arduino.h>
#include "InputButton.hpp"

namespace dankreek {

InputButton::InputButton(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
  this->_pin = pin;
  this->_prevState = (digitalRead(pin) == HIGH);
  this->_curState = this->_prevState;
}

bool InputButton::update() {
  this->_prevState = this->_curState;
  this->_curState = (digitalRead(this->_pin) == HIGH);
  return (this->_prevState != this->_curState);
}

bool InputButton::read() {
  return this->_curState;
}

bool InputButton::fell() {
  return (this->_curState == false) && (this->_prevState == true);
}

bool InputButton::rose() {
  return (this->_curState == true) && (this->_prevState == false);
}

}
