#ifndef FIRE_BUTTONS_IN_H
#define FIRE_BUTTONS_IN_H

#include <IInputButton.hpp>
#include <Pot.hpp>
#include <PwmLed.hpp>
#include "IInputModule.hpp"
#include "InputRouter.hpp"

namespace dankreek {

  class FireButtonsIn {
  public:
    FireButtonsIn(
      IInputButton &aButton, IInputButton &bButton,
      PwmLed &autoFireALed, PwmLed &autoFireBLed,
      Pot &autoFireAPot, Pot &autoFireBPot,
      IInputButton &autoFireSelectA, IInputButton &autoFireSelectB
    );

    virtual void update(InputRouter &inputRouter);

  protected:
    IInputButton *_aButton, *_bButton;
    IInputButton *_autoFireSelectA, *_autoFireSelectB;
    Pot *_autoFireAPot, *_autoFireBPot;
    PwmLed *_autoFireALed, *_autoFireBLed;
  };
}


#endif
