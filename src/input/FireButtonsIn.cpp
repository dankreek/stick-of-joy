#include <Arduino.h>
#include <PwmLed.hpp>
#include <Pot.hpp>
#include "FireButtonsIn.hpp"
#include "IInputButton.hpp"
#include "InputRouter.hpp"

namespace dankreek {
  FireButtonsIn::FireButtonsIn(
    AutoFireButtonIn &autoFireA,
    AutoFireButtonIn &autoFireB
  ) {
    this->_autoFireA = &autoFireA;
    this->_autoFireB = &autoFireB;
  }

  void FireButtonsIn::update(InputRouter &router) {
    if (this->_autoFireA->update()) {
      this->logger.logln("aButton isPressed=", this->_autoFireA->read());
      router.aButton(this->_autoFireA->read());
    }

    if (this->_autoFireB->update()) {
      this->logger.logln("bButton isPressed=", this->_autoFireB->read());
      router.bButton(this->_autoFireB->read());
    }
  }
}
