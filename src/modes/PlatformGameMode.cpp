#include <Logger.hpp>
#include "PlatformGameMode.hpp"


namespace dankreek {

  PlatformGameMode::PlatformGameMode(JoystickOut &joy1, JoystickOut &joy2) {
    this->_joy1 = &joy1;
    this->_joy2 = &joy2;
    this->_joy1->setAllPressed(false);
    this->_joy2->setAllPressed(false);
    this->_upIsPressed = false;
    this->_bIsPressed = false;
    this->_selectedJoystick = &joy2;
  }

  void PlatformGameMode::setUpPressed(bool isPressed) {
      this->_upIsPressed = isPressed;
      if (isPressed || !this->_bIsPressed) {
        this->_selectedJoystick->setUpPressed(isPressed);
      }
  }

  void PlatformGameMode::setBButtonPressed(bool isPressed) {
    this->_bIsPressed = isPressed;
    if (isPressed || !this->_upIsPressed) {
        this->_selectedJoystick->setUpPressed(isPressed);
    }
  }

  void PlatformGameMode::switchTo(
    bool isUpPressed, bool isDownPressed,
    bool isLeftPressed, bool isRightPressed,
    bool isAButtonPressed, bool isBButtonPressed
  ) {
    this->logger.log("switchTo");
    this->setUpPressed(isUpPressed);
    this->_selectedJoystick->setDownPressed(isDownPressed);
    this->_selectedJoystick->setLeftPressed(isLeftPressed);
    this->_selectedJoystick->setRightPressed(isRightPressed);
    this->_selectedJoystick->setFirePressed(isAButtonPressed);
    this->setBButtonPressed(isBButtonPressed);
  }

  void PlatformGameMode::joystickOutSelect() {
    if (this->_selectedJoystick == this->_joy1) {
      logger.log("joystickOutSelect joy2");
      this->_joy1->applyState(this->_joy2);
      this->_joy1->setAllPressed(false);
      this->_selectedJoystick = this->_joy2;
    } else {
      logger.log("joystickOutSelect joy1");
      this->_joy2->applyState(this->_joy1);
      this->_joy2->setAllPressed(false);
      this->_selectedJoystick = this->_joy1;
    }
  }

  void PlatformGameMode::up(bool isPressed) {
    this->logger.log("up isPressed=", isPressed);
    this->setUpPressed(isPressed);
  }

  void PlatformGameMode::down(bool isPressed) {
    this->logger.log("down isPressed=", isPressed);
    this->_selectedJoystick->setDownPressed(isPressed);
  }

  void PlatformGameMode::left(bool isPressed) {
    this->logger.log("left isPressed=", isPressed);
    this->_selectedJoystick->setLeftPressed(isPressed);
  }

  void PlatformGameMode::right(bool isPressed) {
    this->logger.log("right isPresed=", isPressed);
    this->_selectedJoystick->setRightPressed(isPressed);
  }

  void PlatformGameMode::aButton(bool isPressed) {
    this->logger.log("aButton isPressed=", isPressed);
    this->_selectedJoystick->setFirePressed(isPressed);
  }

  void PlatformGameMode::bButton(bool isPressed) {
    this->logger.log("bButton isPressed=", isPressed);
    this->setBButtonPressed(isPressed);
  }
}
