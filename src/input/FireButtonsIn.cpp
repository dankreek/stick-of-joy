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
  }

  void FireButtonsIn::update(InputRouter &router) {
    if (this->_aButton->update()) {
      router.aButton(this->_aButton->fell());
    }

    if (this->_bButton->update()) {
      router.bButton(this->_bButton->fell());
    }
  }
}
