#ifndef JOYSTICK_IN_H
#define JOYSTICK_IN_H

#include <IInputButton.hpp>
#include <Logger.hpp>
#include "IInputModule.hpp"
#include "InputRouter.hpp"

namespace dankreek {

// Receives input from the joystick and sends it off to the input router
class JoystickIn : IInputModule {
public:
  JoystickIn(
    IInputButton &up,
    IInputButton &down,
    IInputButton &left,
    IInputButton &right
  );

  virtual void update(InputRouter &inputRouter);

private:
  Logger logger = Logger("JoystickIn");
  IInputButton* _up;
  IInputButton* _down;
  IInputButton* _left;
  IInputButton* _right;
};

}
#endif
