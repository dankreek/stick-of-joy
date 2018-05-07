#include <Arduino.h>
#include <JoystickOut.hpp>
#include <Logger.hpp>
#include "InputRouter.hpp"
#include "modes/IJoystickMode.hpp"
#include "modes/PlatformGameMode.hpp"


namespace dankreek {
  InputRouter::InputRouter(
    JoystickOut &joystick1Out, JoystickOut &joystick2Out,
    PlatformGameMode &platformGameMode
  ) {
    this->_joy1 = &joystick1Out;
    this->_joy2 = &joystick2Out;
    this->_platformGameMode = &platformGameMode;
    this->_selectedMode = &platformGameMode;

    this->_selectedJoyOutPort = joyOutTwo;
    this->_upIsPressed = false;
    this->_downIsPressed = false;
    this->_leftIsPressed = false;
    this->_rightIsPressed = false;
    this->_aButtonIsPressed = false;
    this->_bButtonIsPressed = false;
  }

  void InputRouter::init() {
    this->_selectedMode->switchTo(
      this->_upIsPressed, this->_downIsPressed,
      this->_leftIsPressed, this->_rightIsPressed,
      this->_aButtonIsPressed, this->_bButtonIsPressed,
      this->_selectedJoyOutPort
    );
  }

  void InputRouter::up(bool isPressed) {
    this->logger.log("up isPressed=", isPressed);
    this->_upIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->up(isPressed);
    }
  }

  void InputRouter::down(bool isPressed) {
    this->logger.log("down isPressed=", isPressed);
    this->_downIsPressed = isPressed;
    this->_selectedMode->down(isPressed);
  }

  void InputRouter::left(bool isPressed) {
    this->logger.log("left isPressed=", isPressed);
    this->_leftIsPressed = isPressed;
    this->_selectedMode->left(isPressed);
  }

  void InputRouter::right(bool isPressed) {
    this->logger.log("right isPressed=", isPressed);
    this->_rightIsPressed = isPressed;
    this->_selectedMode->right(isPressed);
  }

  void InputRouter::aButton(bool isPressed) {
    this->logger.log("aButton isPressed=", isPressed);
    this->_aButtonIsPressed = isPressed;
    this->_selectedMode->aButton(isPressed);
  }

  void InputRouter::bButton(bool isPressed) {
    this->logger.log("bButton isPressed=", isPressed);
    this->_bButtonIsPressed = isPressed;
    this->_selectedMode->bButton(isPressed);
  }

  void InputRouter::outputSelectPressed() {
    this->logger.log("outputSelectPressed");
    this->_selectedJoyOutPort = this->_selectedMode->joystickOutToggle();
  }

  void InputRouter::selectMode(uint8_t modeSelected) {
    this->logger.logln("selectMode", modeSelected);
  }
}
