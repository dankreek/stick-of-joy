#ifndef FIRE_BUTTONS_IN_H
#define FIRE_BUTTONS_IN_H

#include <IInputButton.hpp>
#include "IInputModule.hpp"
#include "InputRouter.hpp"

namespace dankreek {

  class FireButtonsIn {
  public:
    FireButtonsIn(IInputButton &aButton, IInputButton &bButton);

    virtual void update(InputRouter &inputRouter);

  protected:
    IInputButton* _aButton;
    IInputButton* _bButton;
  };
}


#endif
