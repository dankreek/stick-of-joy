#include <Logger.hpp>
#include <PwmLed.hpp>
#include "IJoystickMode.hpp"
#include "DualOutMode.hpp"

namespace dankreek {

  DualOutMode::DualOutMode(
    JoystickOut &joy1, JoystickOut &joy2,
    PwmLed &joy1SelectedLed, PwmLed &joy2SelectedLed
  ) {
    this->_joy1 = &joy1;
    this->_joy2 = &joy2;
    this->_joy1SelectedLed = &joy1SelectedLed;
    this->_joy2SelectedLed = &joy2SelectedLed;
  }

  void DualOutMode::switchTo(
    bool isUpPressed, bool isDownPressed,
    bool isLeftPressed, bool isRightPressed,
    bool isAButtonPressed, bool isBButtonPressed,
    JoystickOutPort joystickOutPort
  ) {
    this->logger.logln("switchTo");

    // Save this here so the previously selected joy out
    // will be selected when the mode is changed
    this->_prevModeJoyOut = joystickOutPort;

    // set both joy out LEDs
    this->_joy1SelectedLed->hardOff();
    this->_joy2SelectedLed->hardOff();
    this->_joy1SelectedLed->softOn(ledOnTimeMs);
    this->_joy2SelectedLed->softOn(ledOnTimeMs);

    this->_joy2->setUpPressed(isUpPressed);
    this->_joy2->setDownPressed(isDownPressed);
    this->_joy2->setLeftPressed(isLeftPressed);
    this->_joy2->setRightPressed(isRightPressed);
    this->_joy1->setFirePressed(isAButtonPressed);
    this->_joy2->setFirePressed(isBButtonPressed);
  }

  void DualOutMode::up(bool isPressed) {
    this->logger.log("up isPressed=", isPressed);
    this->_joy2->setUpPressed(isPressed);
  }

  void DualOutMode::down(bool isPressed) {
    this->logger.log("down isPressed=", isPressed);
    this->_joy2->setDownPressed(isPressed);
  }

  void DualOutMode::left(bool isPressed) {
    this->logger.log("left isPressed=", isPressed);
    this->_joy2->setLeftPressed(isPressed);
  }

  void DualOutMode::right(bool isPressed) {
    this->logger.log("right isPresed=", isPressed);
    this->_joy2->setRightPressed(isPressed);
  }

  void DualOutMode::aButton(bool isPressed) {
    this->logger.log("aButton isPressed=", isPressed);
    this->_joy1->setFirePressed(isPressed);
  }

  void DualOutMode::bButton(bool isPressed) {
    this->logger.log("bButton isPressed=", isPressed);
    this->_joy2->setFirePressed(isPressed);
  }

  JoystickOutPort DualOutMode::joystickOutToggle() {
    this->_joy1SelectedLed->hardOff();
    this->_joy2SelectedLed->hardOff();
    this->_joy1SelectedLed->softOn(ledOnTimeMs);
    this->_joy2SelectedLed->softOn(ledOnTimeMs);

    // Return the output port that was selected while using the previous mode
    return this->_prevModeJoyOut;
  }
}
