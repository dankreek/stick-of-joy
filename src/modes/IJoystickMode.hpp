#ifndef I_JOYSTICK_MODE_H
#define I_JOYSTICK_MODE_H

namespace dankreek {
  class IJoystickMode {
  public:
    IJoystickMode() {};

    // Called when the mode has been selected
    virtual void switchTo(
      bool isUpPressed, bool isDownPressed,
      bool isLeftPressed, bool isRightPressed,
      bool isAButtonPressed, bool isBButtonPressed
    ) = 0;

    // Joystick out toggle was pressed
    virtual void joystickOutSelect() = 0;

    // Joystick inputs
    virtual void up(bool isPressed) = 0;
    virtual void down(bool isPressed) = 0;
    virtual void left(bool isPressed) = 0;
    virtual void right(bool isPressed) = 0;
    virtual void aButton(bool isPressed) = 0;
    virtual void bButton(bool isPressed) = 0;
  };
}

#endif
