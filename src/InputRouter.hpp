#ifndef INPUT_ROUTER_H
#define INPUT_ROUTER_H

#include <Logger.hpp>
#include <JoystickOut.hpp>
#include "modes/IJoystickMode.hpp"
#include "modes/PlatformGameMode.hpp"

namespace dankreek {
  class InputRouter {
  public:
    InputRouter(
      JoystickOut &joystick1Out, JoystickOut &joystick2Out,
      PlatformGameMode &platformGameMode
    );

    void up(bool isPressed);
    void down(bool isPressed);
    void left(bool isPressed);
    void right(bool isPressed);

    void aButton(bool isPressed);
    void bButton(bool isPressed);

    void selectMode(uint8_t modeSelected);
    void outputSelectPressed();

  private:
    Logger logger = Logger("InputRouter");
    JoystickOut* _joy1;
    JoystickOut* _joy2;
    PlatformGameMode* _platformGameMode;

    IJoystickMode* _selectedMode;
  };
}

#endif