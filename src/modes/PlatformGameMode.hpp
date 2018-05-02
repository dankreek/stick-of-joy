#ifndef PLATFORM_GAME_MODE_H
#define PLATFORM_GAME_MODE_H

#include <JoystickOut.hpp>
#include <Logger.hpp>
#include "IJoystickMode.hpp"

namespace dankreek {
  // Mode which routes the B button to UP
  class PlatformGameMode : public IJoystickMode {
  public:
    PlatformGameMode(JoystickOut &joy1, JoystickOut &joy2);

    virtual void switchTo(
      bool isUpPressed, bool isDownPressed,
      bool isLeftPressed, bool isRightPressed,
      bool isAButtonPressed, bool isBButtonPressed
    );

    virtual void joystickOutSelect();

    virtual void up(bool isPressed);
    virtual void down(bool isPressed);
    virtual void left(bool isPressed);
    virtual void right(bool isPressed);
    virtual void aButton(bool isPressed);
    virtual void bButton(bool isPressed);

  protected:
    Logger logger = Logger("PlatformGameMode");
    JoystickOut *_joy1, *_joy2;
    JoystickOut *_selectedJoystick;
    bool _upIsPressed;
    bool _bIsPressed;

    void setUpPressed(bool isPressed);
    void setBButtonPressed(bool isPressed);
  };
}

#endif
