#ifndef MODE_SELECTORS_IN
#define MODE_SELECTORS_IN

#include <IInputButton.hpp>
#include "IInputModule.hpp"
#include "InputRouter.hpp"

namespace dankreek {
  class ModeSelectorsIn : IInputModule {
  public:
    ModeSelectorsIn(
      IInputButton &mode1,
      IInputButton &mode2,
      IInputButton &mode3,
      IInputButton &outputSelect
    );

    void update(InputRouter &inputRouter);

  protected:
    IInputButton *_mode1, *_mode2, *_mode3, *_outputSelect;
  };
}

#endif
