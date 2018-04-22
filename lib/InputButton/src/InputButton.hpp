#ifndef INPUT_BUTTON_H
#define INPUT_BUTTON_H
#include <cstdint>
#include "IInputButton.hpp"

namespace dankreek {

class InputButton : public IInputButton {
protected:
  uint8_t _pin;
  bool _prevState;
  bool _curState;

public:
  InputButton(uint8_t pin);
  virtual bool update();
  virtual bool read();
  virtual bool fell();
  virtual bool rose();
};
}
#endif
