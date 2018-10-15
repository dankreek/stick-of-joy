#ifndef MODE_SELECTORS_IN
#define MODE_SELECTORS_IN

#include <IInputButton.hpp>
#include <PwmLed.hpp>
#include "IInputModule.hpp"
#include "InputRouter.hpp"
#include "modes/IJoystickMode.hpp"
#include "modes/SingleButtonMode.hpp"
#include "modes/PlatformGameMode.hpp"
#include "modes/DualOutMode.hpp"

namespace dankreek {
  class ModeSelectorsIn : IInputModule {
  public:
    ModeSelectorsIn(
      IInputButton &mode1,
      IInputButton &mode2,
      IInputButton &mode3,
      IInputButton &outputSelect,

      SingleButtonMode &singleButtonMode,
      PlatformGameMode &platformGameMode,
      DualOutMode &dualOutMode,

      // The individual modes actually control the LED's but these
      // are referenced in this class so that they can be updated
      // on every cycle
      PwmLed &joy1SelectedLed,
      PwmLed &joy2SelectedLed
    );

    void update(InputRouter &inputRouter);

  protected:
    IInputButton *_mode1, *_mode2, *_mode3, *_outputSelect;
    IJoystickMode *_singleButtonMode, *_platformGameMode, *_dualOutMode;
    PwmLed *_joy1SelectedLed, *_joy2SelectedLed;
  };
}

#endif
