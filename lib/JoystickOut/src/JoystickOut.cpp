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

  this->isPressed = false;
}

void OutputButton::setPressed(bool isPressed) {
  if (isPressed != this->isPressed) {
    this->isPressed = isPressed;

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
  this->upButton = &upButton;
  this->downButton = &downButton;
  this->leftButton = &leftButton;
  this->rightButton = &rightButton;
  this->fireButton = &fireButton;
}

void JoystickOut::setUpPressed(bool isPressed) {
  this->upButton->setPressed(isPressed);
  this->logger.logln("setUpPressed isPressed=", isPressed);
}

void JoystickOut::setDownPressed(bool isPressed) {
  this->downButton->setPressed(isPressed);
  this->logger.logln("setDownPressed isPressed=", isPressed);
}

void JoystickOut::setLeftPressed(bool isPressed) {
  this->leftButton->setPressed(isPressed);
  this->logger.logln("setLeftPressed isPressed=", isPressed);
}

void JoystickOut::setRightPressed(bool isPressed) {
  this->rightButton->setPressed(isPressed);
  this->logger.logln("setRightPressed isPressed=", isPressed);
}

void JoystickOut::setFirePressed(bool isPressed) {
  this->fireButton->setPressed(isPressed);
  this->logger.logln("setFirePressed isPressed=", isPressed);
}

void JoystickOut::setAllPressed(bool isPressed) {
  this->upButton->setPressed(isPressed);
  this->downButton->setPressed(isPressed);
  this->leftButton->setPressed(isPressed);
  this->rightButton->setPressed(isPressed);
  this->fireButton->setPressed(isPressed);
  this->logger.logln("setAllPressed isPressed=", isPressed);
}

void JoystickOut::applyState(JoystickOut *other) {
  other->setUpPressed(this->upButton->isPressed);
  other->setDownPressed(this->downButton->isPressed);
  other->setLeftPressed(this->leftButton->isPressed);
  other->setRightPressed(this->rightButton->isPressed);
  other->setFirePressed(this->fireButton->isPressed);
}

}
