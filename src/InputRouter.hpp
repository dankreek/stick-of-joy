#ifndef INPUT_ROUTER_H
#define INPUT_ROUTER_H

#include <Logger.hpp>
#include <JoystickOut.hpp>
#include "modes/IJoystickMode.hpp"
#include "modes/PlatformGameMode.hpp"
#include "modes/SingleButtonMode.hpp"
#include "modes/DualOutMode.hpp"

namespace dankreek {
  class InputRouter {
  public:
    InputRouter(
      JoystickOut &joystick1Out, JoystickOut &joystick2Out,
      PlatformGameMode &platformGameMode,
      SingleButtonMode &singleButtonMode,
      DualOutMode &dualOutMode
    );

    void init();

    void up(bool isPressed);
    void down(bool isPressed);
    void left(bool isPressed);
    void right(bool isPressed);

    void aButton(bool isPressed);
    void bButton(bool isPressed);

    void selectMode(IJoystickMode::SelectedMode selectedMode);
    void outputSelectPressed();

  private:
    Logger logger = Logger("InputRouter");
    JoystickOut* _joy1;
    JoystickOut* _joy2;

    bool _upIsPressed, _downIsPressed,
         _leftIsPressed, _rightIsPressed,
         _aButtonIsPressed, _bButtonIsPressed;
    JoystickOutPort _selectedJoyOutPort;

    PlatformGameMode* _platformGameMode;
    SingleButtonMode* _singleButtonMode;
    DualOutMode* _dualOutMode;
    IJoystickMode* _selectedMode;
  };
}

#endif
