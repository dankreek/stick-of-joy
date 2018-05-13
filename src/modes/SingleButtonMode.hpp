#ifndef SINGLE_BUTTON_MODE_H
#define SINGLE_BUTTON_MODE_H

#include <JoystickOut.hpp>
#include <Logger.hpp>
#include <PwmLed.hpp>
#include "IJoystickMode.hpp"

namespace dankreek {
  // Mode which routes the A and B buttons to fire
  class SingleButtonMode : public IJoystickMode {
  public:
    SingleButtonMode(
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
    Logger logger = Logger("SingleButtonMode");
    JoystickOut *_joy1, *_joy2;
    JoystickOut *_selectedJoystick;
    PwmLed *_joy1SelectedLed, *_joy2SelectedLed;
    bool _aIsPressed;
    bool _bIsPressed;

    void setJoyOutLeds(JoystickOutPort joystickOutPort);
    void setAButtonPressed(bool isPressed);
    void setBButtonPressed(bool isPressed);
  };
}

#endif
