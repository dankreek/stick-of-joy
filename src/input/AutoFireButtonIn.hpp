#ifndef AUTOFIRE_BUTTON_IN_H
#define AUTOFIRE_BUTTON_IN_H

#include <Logger.hpp>
#include <IInputButton.hpp>
#include <Pot.hpp>
#include <PwmLed.hpp>
#include <Arduino.h>

namespace dankreek {

  class AutoFireButtonIn {
  public:
    AutoFireButtonIn(
      IInputButton &button, PwmLed &autoFireLed,
      Pot &autoFirePot, IInputButton &autoFireSelect,
      const char* buttonName
    );

    // Update the autofire button and controls
    // Return true if the button is in a new logical state
    bool update();

    // Return true if the button is logically down
    bool read();

  private:
    const uint16_t ledSelectTimeMs = 50;
    const uint16_t ledDeselectTimeMs = 180;

    Logger *_logger;
    IInputButton *_button;
    PwmLed *_led;
    Pot *_pot;
    IInputButton *_autoFireSelect;
    bool _wasLogicallyDown;
    bool _isLogicallyDown;

    unsigned long _autoFireTime_us;
    elapsedMicros _timeSincePress_us;

    void updateButtonPress();
    void updateAutoFireState();
    void updateAutoFireRate();

    void setNewLogicalState(bool isDown);
    bool isLogicalStateChanged();
    bool isAutoFireSelected();

    static unsigned long calculateAutoFireTime_us(uint16_t potVal);
  };
}

#endif
