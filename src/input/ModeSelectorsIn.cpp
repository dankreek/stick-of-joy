#include "ModeSelectorsIn.hpp"
#include "InputRouter.hpp"
#include "IInputButton.hpp"

namespace dankreek {

  ModeSelectorsIn::ModeSelectorsIn(
    IInputButton &mode1,
    IInputButton &mode2,
    IInputButton &mode3,
    IInputButton &outputSelect,

    SingleButtonMode &singleButtonMode,
    PlatformGameMode &platformGameMode,
    DualOutMode &dualOutMode,

    PwmLed &joy1SelectedLed,
    PwmLed &joy2SelectedLed
  ) {
    this->_mode1 = &mode1;
    this->_mode2 = &mode2;
    this->_mode3 = &mode3;
    this->_outputSelect = &outputSelect;

    this->_singleButtonMode = &singleButtonMode;
    this->_platformGameMode = &platformGameMode;
    this->_dualOutMode = &dualOutMode;

    this->_joy1SelectedLed = &joy1SelectedLed;
    this->_joy2SelectedLed = &joy2SelectedLed;
  }

  void ModeSelectorsIn::update(InputRouter &inputRouter) {
    this->_joy1SelectedLed->update();
    this->_joy2SelectedLed->update();

    if (this->_mode1->update() && this->_mode1->fell()) {
        inputRouter.selectMode(this->_singleButtonMode);
    }

    if (this->_mode2->update() && this->_mode2->fell()) {
      inputRouter.selectMode(this->_platformGameMode);
    }

    if (this->_mode3->update() && this->_mode3->fell()) {
      inputRouter.selectMode(this->_dualOutMode);
    }

    if (this->_outputSelect->update() && this->_outputSelect->fell()) {
      inputRouter.outputSelectPressed();
    }
  }
}
