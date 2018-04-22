#ifndef IINPUT_BUTTON
#define IINPUT_BUTTON

namespace dankreek {

class IInputButton {
public:
  IInputButton(){};
  virtual ~IInputButton(){};

  // Poll to update the state of the button reder
  virtual bool update() = 0;

  // Return the current state of the button after an update()
  virtual bool read() = 0;

  // Has the pin fallen from HIGH to LOW?
  virtual bool fell() = 0;

  // Has the pin risen from LOW to HIGH?
  virtual bool rose() = 0;
};
}

#endif
