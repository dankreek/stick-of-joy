#include <Arduino.h>
#include "FireButtonsIn.hpp"
#include "IInputButton.hpp"
#include "InputRouter.hpp"

namespace dankreek {
  FireButtonsIn::FireButtonsIn(IInputButton &aButton, IInputButton &bButton) {
    this->_aButton = &aButton;
    this->_bButton = &bButton;
  }

  void FireButtonsIn::update(InputRouter &router) {
    if (this->_aButton->update()) {
      router.aButton(this->_aButton->fell());
    }

    if (this->_bButton->update()) {
      Serial.println("B button changed");
      router.bButton(this->_bButton->fell());
    }
  }
}
