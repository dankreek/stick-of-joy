#ifndef I_JOYSTICK_MODE_H
#define I_JOYSTICK_MODE_H

#include <Arduino.h>

namespace dankreek {
  enum JoystickOutPort {
    joyOutOne, joyOutTwo
  };

  class IJoystickMode {
  public:
    enum SelectedMode {
      singleFire,
      platform,
      dualPort
    };

    IJoystickMode() {};

    // Called when the mode has been selected
    virtual void switchTo(
      bool isUpPressed, bool isDownPressed,
      bool isLeftPressed, bool isRightPressed,
      bool isAButtonPressed, bool isBButtonPressed,
      JoystickOutPort selectedOutPort
    ) = 0;

    // Joystick out toggle was pressed
    virtual JoystickOutPort joystickOutToggle() = 0;

    // Joystick inputs
    virtual void up(bool isPressed) = 0;
    virtual void down(bool isPressed) = 0;
    virtual void left(bool isPressed) = 0;
    virtual void right(bool isPressed) = 0;
    virtual void aButton(bool isPressed) = 0;
    virtual void bButton(bool isPressed) = 0;

  protected:
    const uint16_t ledOnTimeMs = 50;
    const uint16_t ledOffTimeMs = 180;
  };
}

#endif
