#ifndef DEBOUNCED_INPUT_BUTTON_H
#define DEBOUNCED_INPUT_BUTTON_H

#include <Bounce2.h>
#include "IInputButton.hpp"

namespace dankreek {

class DebouncedInputButton : public IInputButton {
protected:
  Bounce _debouncer;

public:
  DebouncedInputButton(uint8_t pin, unsigned long intervalMS);

  virtual bool update();
  virtual bool read();
  virtual bool fell();
  virtual bool rose();
};

}

#endif
