#include <Arduino.h>
#include <Logger.hpp>
#include <IInputButton.hpp>
#include "InputRouter.hpp"
#include "JoystickIn.hpp"

namespace dankreek {
  JoystickIn::JoystickIn(
    IInputButton &up,
    IInputButton &down,
    IInputButton &left,
    IInputButton &right
  ) {
    this->_up = &up;
    this->_down = &down;
    this->_left = &left;
    this->_right = &right;
  }

  void JoystickIn::update(InputRouter &inputRouter) {
    if (this->_up->update()) {
      inputRouter.up(this->_up->fell());
    }

    if (this->_down->update()) {
      inputRouter.down(this->_down->fell());
    }

    if (this->_left->update()) {
      inputRouter.left(this->_left->fell());
    }

    if (this->_right->update()) {
      inputRouter.right(this->_right->fell());
    }
  }
}
