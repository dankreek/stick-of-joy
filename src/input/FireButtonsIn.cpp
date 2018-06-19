#include <Arduino.h>
#include <PwmLed.hpp>
#include <Pot.hpp>
#include "FireButtonsIn.hpp"
#include "IInputButton.hpp"
#include "InputRouter.hpp"

namespace dankreek {
  FireButtonsIn::FireButtonsIn(
    IInputButton &aButton, IInputButton &bButton,
    PwmLed &autoFireALed, PwmLed &autoFireBLed,
    Pot &autoFireAPot, Pot &autoFireBPot,
    IInputButton &autoFireSelectA, IInputButton &autoFireSelectB
  ) {
    this->_aButton = &aButton;
    this->_bButton = &bButton;
    this->_autoFireALed = &autoFireALed;
    this->_autoFireBLed = &autoFireBLed;
    this->_autoFireAPot = &autoFireAPot;
    this->_autoFireBPot = &autoFireBPot;
    this->_autoFireSelectA = &autoFireSelectA;
    this->_autoFireSelectB = &autoFireSelectB;

    // Do an update on the autofire select buttons so they can be read.
    // This is required because the auto-fire select buttons are
    // aren't momentary, so they could be on when the joystick is powered up.
    this->_autoFireSelectA->update();
    this->_autoFireSelectB->update();

    this->updateAutoFireA(!this->_autoFireSelectA->read());
    this->updateAutoFireB(!this->_autoFireSelectB->read());
  }

  void FireButtonsIn::updateAutoFireA(bool isSelected) {
    if (isSelected) {
      this->_autoFireALed->softOn(ledOnTimeMs);
    }
    else {
      this->_autoFireALed->softOff(ledOffTimeMs);
    }
  }

  void FireButtonsIn::updateAutoFireB(bool isSelected) {
    if (isSelected) {
      this->_autoFireBLed->softOn(ledOnTimeMs);
    }
    else {
      this->_autoFireBLed->softOff(ledOffTimeMs);
    }
  }

  void FireButtonsIn::update(InputRouter &router) {
    this->_autoFireALed->update();
    this->_autoFireBLed->update();

    if (this->_aButton->update()) {
      router.aButton(this->_aButton->fell());
    }

    if (this->_bButton->update()) {
      router.bButton(this->_bButton->fell());
    }

    if (this->_autoFireSelectA->update()) {
      this->updateAutoFireA(!this->_autoFireSelectA->read());
    }

    if (this->_autoFireSelectB->update()) {
      this->updateAutoFireB(!this->_autoFireSelectB->read());
    }

    if (this->_autoFireAPot->update()) {
      this->logger.logln("Autofire A Pot=", this->_autoFireAPot->read());
    }

    if (this->_autoFireBPot->update()) {
      this->logger.logln("Autofire B Pot=", this->_autoFireBPot->read());
    }
  }
}
