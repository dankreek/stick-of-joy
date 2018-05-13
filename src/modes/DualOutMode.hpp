#ifndef DUAL_OUT_MODE_H
#define DUAL_OUT_MODE_H

#include <JoystickOut.hpp>
#include <Logger.hpp>
#include <PwmLed.hpp>
#include "IJoystickMode.hpp"

namespace dankreek {
  class DualOutMode : public IJoystickMode {
  public:
    DualOutMode(
      JoystickOut &joy1, JoystickOut &joy2,
      PwmLed &joy1SelectedLed, PwmLed &joy2SelectedLed
    );

    virtual void switchTo(
      bool isUpPressed, bool isDownPressed,
      bool isLeftPressed, bool isRightPressed,
      bool isAButtonPressed, bool isBButtonPressed,
      JoystickOutPort selectedOutPort
    );

    virtual JoystickOutPort joystickOutToggle();

    virtual void up(bool isPressed);
    virtual void down(bool isPressed);
    virtual void left(bool isPressed);
    virtual void right(bool isPressed);
    virtual void aButton(bool isPressed);
    virtual void bButton(bool isPressed);

  protected:
    Logger logger = Logger("DualOutMode");
    JoystickOut *_joy1, *_joy2;
    PwmLed *_joy1SelectedLed, *_joy2SelectedLed;
    JoystickOutPort _prevModeJoyOut;

  };
}

#endif
