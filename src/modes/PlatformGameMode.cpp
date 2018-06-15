#include <Logger.hpp>
#include <PwmLed.hpp>
#include "IJoystickMode.hpp"
#include "PlatformGameMode.hpp"

namespace dankreek {

  PlatformGameMode::PlatformGameMode(
    JoystickOut &joy1, JoystickOut &joy2,
    PwmLed &joy1SelectedLed, PwmLed &joy2SelectedLed
  ) {
    this->_joy1 = &joy1;
    this->_joy2 = &joy2;
    this->_joy1SelectedLed = &joy1SelectedLed;
    this->_joy2SelectedLed = &joy2SelectedLed;
    this->_upIsPressed = false;
    this->_aIsPressed = false;

    // Shouldn't matter, but set to avoid possible null pointer deref
    this->_selectedJoystick = &joy2;
  }

  void PlatformGameMode::switchTo(
    bool isUpPressed, bool isDownPressed,
    bool isLeftPressed, bool isRightPressed,
    bool isAButtonPressed, bool isBButtonPressed,
    JoystickOutPort joystickOutPort
  ) {
    this->logger.logln("switchTo");

    this->setJoyOutLeds(joystickOutPort);

    if (joystickOutPort == joyOutOne) {
      this->_selectedJoystick = this->_joy1;
    } else {
      this->_selectedJoystick = this->_joy2;
    }

    this->setUpPressed(isUpPressed);
    this->_selectedJoystick->setDownPressed(isDownPressed);
    this->_selectedJoystick->setLeftPressed(isLeftPressed);
    this->_selectedJoystick->setRightPressed(isRightPressed);
    this->_selectedJoystick->setFirePressed(isBButtonPressed);
    this->setAButtonPressed(isAButtonPressed);
  }

  void PlatformGameMode::setUpPressed(bool isPressed) {
      this->_upIsPressed = isPressed;
      if (isPressed || !this->_aIsPressed) {
        this->_selectedJoystick->setUpPressed(isPressed);
      }
  }

  void PlatformGameMode::setAButtonPressed(bool isPressed) {
    this->_aIsPressed = isPressed;
    if (isPressed || !this->_upIsPressed) {
        this->_selectedJoystick->setUpPressed(isPressed);
    }
  }

  JoystickOutPort PlatformGameMode::joystickOutToggle() {
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

  void PlatformGameMode::bButton(bool isPressed) {
    this->logger.log("bButton isPressed=", isPressed);
    this->_selectedJoystick->setFirePressed(isPressed);
  }

  void PlatformGameMode::aButton(bool isPressed) {
    this->logger.log("aButton isPressed=", isPressed);
    this->setAButtonPressed(isPressed);
  }

  void PlatformGameMode::setJoyOutLeds(JoystickOutPort joystickOutPort) {
    if (joystickOutPort == joyOutOne) {
      this->_joy1SelectedLed->setBrightness(0x10);
      this->_joy2SelectedLed->setBrightness(0x00);
    } else {
      this->_joy1SelectedLed->setBrightness(0x00);
      this->_joy2SelectedLed->setBrightness(0x10);
    }
  }
}
