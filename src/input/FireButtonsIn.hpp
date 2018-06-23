#ifndef FIRE_BUTTONS_IN_H
#define FIRE_BUTTONS_IN_H

#include <Logger.hpp>
#include <IInputButton.hpp>
#include <Pot.hpp>
#include <PwmLed.hpp>
#include "AutoFireButtonIn.hpp"
#include "IInputModule.hpp"
#include "InputRouter.hpp"

namespace dankreek {

  class FireButtonsIn {
  public:
    FireButtonsIn(
      AutoFireButtonIn &autoFireA,
      AutoFireButtonIn &autoFireB
    );

    virtual void update(InputRouter &inputRouter);

  protected:
    Logger logger = Logger("FireButtonsIn");
    AutoFireButtonIn* _autoFireA;
    AutoFireButtonIn* _autoFireB;
  };
}


#endif
