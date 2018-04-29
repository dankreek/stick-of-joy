#include "PlatformGameMode.hpp"

namespace dankreek {
  PlatformGameMode::PlatformGameMode(JoystickOut &joy1, JoystickOut &joy2) {
    this->_joy1 = &joy1;
    this->_joy2 = &joy2;
    this->_selectedJoystick = &joy2;
  }

  void PlatformGameMode::switchTo() {
    this->_joy1->setAllPressed(false);
    this->_joy2->setAllPressed(false);
  }

  void PlatformGameMode::switchFrom() {
    this->_selectedJoystick->setAllPressed(false);
  }

  void PlatformGameMode::joystickOutSelect() {
    if (this->_selectedJoystick == this->_joy1) {
      this->_joy1->setAllPressed(false);
      this->_selectedJoystick = this->_joy2;
    } else {
      this->_joy2->setAllPressed(false);
      this->_selectedJoystick = this->_joy1;
    }
  }

  void PlatformGameMode::up(bool isPressed) {
    this->_selectedJoystick->setUpPressed(isPressed);
  }

  void PlatformGameMode::down(bool isPressed) {
    this->_selectedJoystick->setDownPressed(isPressed);
  }

  void PlatformGameMode::left(bool isPressed) {
    this->_selectedJoystick->setLeftPressed(isPressed);
  }

  void PlatformGameMode::right(bool isPressed) {
    this->_selectedJoystick->setRightPressed(isPressed);
  }

  void PlatformGameMode::aButton(bool isPressed) {
    this->_selectedJoystick->setFirePressed(isPressed);
  }

  void PlatformGameMode::bButton(bool isPressed) {
    this->_selectedJoystick->setUpPressed(isPressed);
  }
}
