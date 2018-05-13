#include <Logger.hpp>
#include <PwmLed.hpp>
#include "IJoystickMode.hpp"
#include "SingleButtonMode.hpp"

namespace dankreek {
  SingleButtonMode::SingleButtonMode(
    JoystickOut &joy1, JoystickOut &joy2,
    PwmLed &joy1SelectedLed, PwmLed &joy2SelectedLed
  ) {
    this->_joy1 = &joy1;
    this->_joy2 = &joy2;
    this->_joy1SelectedLed = &joy1SelectedLed;
    this->_joy2SelectedLed = &joy2SelectedLed;
    this->_aIsPressed = false;
    this->_bIsPressed = false;

    // Shouldn't matter, but set to avoid possible null pointer deref
    this->_selectedJoystick = &joy2;
  }

  void SingleButtonMode::switchTo(
    bool isUpPressed, bool isDownPressed,
    bool isLeftPressed, bool isRightPressed,
    bool isAButtonPressed, bool isBButtonPressed,
    JoystickOutPort joystickOutPort
  ) {
    this->logger.log("switchTo");

    this->setJoyOutLeds(joystickOutPort);

    if (joystickOutPort == joyOutOne) {
      this->_selectedJoystick = this->_joy1;
    } else {
      this->_selectedJoystick = this->_joy2;
    }

    this->_selectedJoystick->setUpPressed(isUpPressed);
    this->_selectedJoystick->setDownPressed(isDownPressed);
    this->_selectedJoystick->setLeftPressed(isLeftPressed);
    this->_selectedJoystick->setRightPressed(isRightPressed);
    this->setAButtonPressed(isAButtonPressed);
    this->setBButtonPressed(isBButtonPressed);
  }

  void SingleButtonMode::setAButtonPressed(bool isPressed) {
    this->_aIsPressed = isPressed;
    if (isPressed || !this->_bIsPressed) {
        this->_selectedJoystick->setFirePressed(isPressed);
    }
  }

  void SingleButtonMode::setBButtonPressed(bool isPressed) {
    this->_bIsPressed = isPressed;
    if (isPressed || !this->_aIsPressed) {
        this->_selectedJoystick->setFirePressed(isPressed);
    }
  }

  JoystickOutPort SingleButtonMode::joystickOutToggle() {
    if (this->_selectedJoystick == this->_joy1) {
      logger.log("joystickOutSelect joy2");
      this->_joy1->applyState(this->_joy2);
      this->_joy1->setAllPressed(false);
      this->_selectedJoystick = this->_joy2;
      this->setJoyOutLeds(joyOutTwo);
      return joyOutTwo;
    } else {
      logger.log("joystickOutSelect joy1");
      this->_joy2->applyState(this->_joy1);
      this->_joy2->setAllPressed(false);
      this->_selectedJoystick = this->_joy1;
      this->setJoyOutLeds(joyOutOne);
      return joyOutOne;
    }
  }

  void SingleButtonMode::up(bool isPressed) {
    this->logger.log("up isPressed=", isPressed);
    this->_selectedJoystick->setUpPressed(isPressed);
  }

  void SingleButtonMode::down(bool isPressed) {
    this->logger.log("down isPressed=", isPressed);
    this->_selectedJoystick->setDownPressed(isPressed);
  }

  void SingleButtonMode::left(bool isPressed) {
    this->logger.log("left isPressed=", isPressed);
    this->_selectedJoystick->setLeftPressed(isPressed);
  }

  void SingleButtonMode::right(bool isPressed) {
    this->logger.log("right isPresed=", isPressed);
    this->_selectedJoystick->setRightPressed(isPressed);
  }

  void SingleButtonMode::bButton(bool isPressed) {
    this->logger.log("bButton isPressed=", isPressed);
    this->setBButtonPressed(isPressed);
  }

  void SingleButtonMode::aButton(bool isPressed) {
    this->logger.log("aButton isPressed=", isPressed);
    this->setAButtonPressed(isPressed);
  }

  void SingleButtonMode::setJoyOutLeds(JoystickOutPort joystickOutPort) {
    if (joystickOutPort == joyOutOne) {
      this->_joy1SelectedLed->constant(0xff);
      this->_joy2SelectedLed->constant(0x00);
    } else {
      this->_joy1SelectedLed->constant(0x00);
      this->_joy2SelectedLed->constant(0xff);
    }
  }
}
