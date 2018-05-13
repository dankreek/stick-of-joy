#include "modes/IJoystickMode.hpp"
#include "ModeSelectorsIn.hpp"
#include "InputRouter.hpp"
#include "IInputButton.hpp"

namespace dankreek {

  ModeSelectorsIn::ModeSelectorsIn(
    IInputButton &mode1,
    IInputButton &mode2,
    IInputButton &mode3,
    IInputButton &outputSelect
  ) {
    this->_mode1 = &mode1;
    this->_mode2 = &mode2;
    this->_mode3 = &mode3;
    this->_outputSelect = &outputSelect;
  }

  void ModeSelectorsIn::update(InputRouter &inputRouter) {
    if (this->_mode1->update() && this->_mode1->fell()) {
        inputRouter.selectMode(IJoystickMode::singleFire);
    }

    if (this->_mode2->update() && this->_mode2->fell()) {
      inputRouter.selectMode(IJoystickMode::platform);
    }

    if (this->_mode3->update() && this->_mode3->fell()) {
      inputRouter.selectMode(IJoystickMode::dualPort);
    }

    if (this->_outputSelect->update() && this->_outputSelect->fell()) {
      inputRouter.outputSelectPressed();
    }
  }
}
