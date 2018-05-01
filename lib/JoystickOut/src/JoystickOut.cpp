#include <Arduino.h>
#include <cstdint>
#include "JoystickOut.hpp"

namespace dankreek {

OutputButton::OutputButton(uint8_t pin) {
  this->_pin = pin;

  // Initialize the pin for low output, then disconnected it
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);

  this->_isPressed = false;
}

void OutputButton::setPressed(bool isPressed) {
  if (isPressed != this->_isPressed) {
    this->_isPressed = isPressed;

    if (isPressed) {
      pinMode(this->_pin, OUTPUT);
    }
    else {
      // Set pin to high-z so that the reader sees no connection
      pinMode(this->_pin, INPUT);
    }
  }
}

JoystickOut::JoystickOut(
  OutputButton &upButton,
  OutputButton &downButton,
  OutputButton &leftButton,
  OutputButton &rightButton,
  OutputButton &fireButton
) {
  this->_upButton = &upButton;
  this->_downButton = &downButton;
  this->_leftButton = &leftButton;
  this->_rightButton = &rightButton;
  this->_fireButton = &fireButton;
}

void JoystickOut::setUpPressed(bool isPressed) {
  this->_upButton->setPressed(isPressed);
  this->logger.log("setUpPressed isPressed=", isPressed);
}

void JoystickOut::setDownPressed(bool isPressed) {
  this->_downButton->setPressed(isPressed);
  this->logger.log("setDownPressed isPressed=", isPressed);
}

void JoystickOut::setLeftPressed(bool isPressed) {
  this->_leftButton->setPressed(isPressed);
  this->logger.log("setLeftPressed isPressed=", isPressed);
}

void JoystickOut::setRightPressed(bool isPressed) {
  this->_rightButton->setPressed(isPressed);
  this->logger.log("setRightPressed isPressed=", isPressed);
}

void JoystickOut::setFirePressed(bool isPressed) {
  this->_fireButton->setPressed(isPressed);
  this->logger.log("setFirePressed isPressed=", isPressed);
}

void JoystickOut::setAllPressed(bool isPressed) {
  this->_upButton->setPressed(isPressed);
  this->_downButton->setPressed(isPressed);
  this->_leftButton->setPressed(isPressed);
  this->_rightButton->setPressed(isPressed);
  this->_fireButton->setPressed(isPressed);
  this->logger.log("setAllPressed isPressed=", isPressed);
}

}
