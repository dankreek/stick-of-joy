#ifndef JOYSTICKOUT_H
#define JOYSTICKOUT_H

#include <cstdint>

namespace dankreek {

class OutputButton {
public:
  OutputButton(uint8_t pin);
  void setPressed(bool isPressed);
protected:
  bool _isPressed;
  uint8_t _pin;
};

  // Joystick Output interface.
class JoystickOut {
public:
  JoystickOut(
    OutputButton &upButton,
    OutputButton &downButton,
    OutputButton &leftButton,
    OutputButton &rightButton,
    OutputButton &fireButton
  );

  // Send Joystick direction or button on or off.
  void setUpPressed(bool isPressed);
  void setDownPressed(bool isPressed);
  void setLeftPressed(bool isPressed);
  void setRightPressed(bool isPressed);
  void setFirePressed(bool isPressed);

  // Send isPressed to all directions and fire button
  void setAllPressed(bool isPressed);

protected:
  OutputButton *_upButton, *_downButton, *_leftButton, *_rightButton, *_fireButton;
};
}
#endif
