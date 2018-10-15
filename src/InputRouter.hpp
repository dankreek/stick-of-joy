#ifndef INPUT_ROUTER_H
#define INPUT_ROUTER_H

#include <Logger.hpp>
#include <JoystickOut.hpp>
#include "modes/IJoystickMode.hpp"

namespace dankreek {
  class InputRouter {
  public:
    InputRouter(JoystickOut &joystick1Out, JoystickOut &joystick2Out);

    void up(bool isPressed);
    void down(bool isPressed);
    void left(bool isPressed);
    void right(bool isPressed);

    void aButton(bool isPressed);
    void bButton(bool isPressed);

    void selectMode(IJoystickMode* selectedMode);
    void outputSelectPressed();

  private:
    Logger logger = Logger("InputRouter");
    JoystickOut* _joy1;
    JoystickOut* _joy2;

    bool _upIsPressed, _downIsPressed,
         _leftIsPressed, _rightIsPressed,
         _aButtonIsPressed, _bButtonIsPressed;

    JoystickOutPort _selectedJoyOutPort;
    IJoystickMode* _selectedMode;
  };
}

#endif
