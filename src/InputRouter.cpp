#include <Arduino.h>
#include <JoystickOut.hpp>
#include <Logger.hpp>
#include "InputRouter.hpp"
#include "modes/IJoystickMode.hpp"
#include "modes/PlatformGameMode.hpp"
#include "modes/SingleButtonMode.hpp"
#include "modes/DualOutMode.hpp"

namespace dankreek {
  InputRouter::InputRouter(JoystickOut &joystick1Out, JoystickOut &joystick2Out) {
    this->_selectedMode = NULL;

    this->_joy1 = &joystick1Out;
    this->_joy2 = &joystick2Out;

    // Default joystick output port is 2, the common one
    this->_selectedJoyOutPort = joyOutTwo;

    this->_upIsPressed = false;
    this->_downIsPressed = false;
    this->_leftIsPressed = false;
    this->_rightIsPressed = false;
    this->_aButtonIsPressed = false;
    this->_bButtonIsPressed = false;
  }

  void InputRouter::up(bool isPressed) {
    this->logger.logln("up isPressed=", isPressed);
    this->_upIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->up(isPressed);
    }
  }

  void InputRouter::down(bool isPressed) {
    this->logger.logln("down isPressed=", isPressed);
    this->_downIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->down(isPressed);
    }
  }

  void InputRouter::left(bool isPressed) {
    this->logger.logln("left isPressed=", isPressed);
    this->_leftIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->left(isPressed);
    }
  }

  void InputRouter::right(bool isPressed) {
    this->logger.logln("right isPressed=", isPressed);
    this->_rightIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->right(isPressed);
    }
  }

  void InputRouter::aButton(bool isPressed) {
    this->logger.logln("aButton isPressed=", isPressed);
    this->_aButtonIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->aButton(isPressed);
    }
  }

  void InputRouter::bButton(bool isPressed) {
    this->logger.logln("bButton isPressed=", isPressed);
    this->_bButtonIsPressed = isPressed;
    if (this->_selectedMode != NULL) {
      this->_selectedMode->bButton(isPressed);
    }
  }

  void InputRouter::outputSelectPressed() {
    this->logger.logln("outputSelectPressed");
    if (this->_selectedMode != NULL) {
      this->_selectedJoyOutPort = this->_selectedMode->joystickOutToggle();
    }
  }

  void InputRouter::selectMode(IJoystickMode* selectedMode) {
    this->_selectedMode = selectedMode;

    this->_selectedMode->switchTo(
      this->_upIsPressed, this->_downIsPressed,
      this->_leftIsPressed, this->_rightIsPressed,
      this->_aButtonIsPressed, this->_bButtonIsPressed,
      this->_selectedJoyOutPort
    );
  }
}
