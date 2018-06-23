#include "AutoFireButtonIn.hpp"
#include <Logger.hpp>
#include <IInputButton.hpp>
#include <Pot.hpp>
#include <PwmLed.hpp>
#include <Arduino.h>

namespace dankreek {
  AutoFireButtonIn::AutoFireButtonIn(
      IInputButton &button, PwmLed &autoFireLed,
      Pot &autoFirePot, IInputButton &autoFireSelect,
      const char* buttonName
  ) {
    this->_button = &button;
    this->_led = &autoFireLed;
    this->_pot = &autoFirePot;
    this->_autoFireSelect = &autoFireSelect;
    this->_logger = new Logger(buttonName);

    this->_wasLogicallyDown = (this->_button->read() == LOW);
    this->_isLogicallyDown = this->_wasLogicallyDown;

    this->updateAutoFireState();
    this->updateAutoFireRate();
    this->updateButtonPress();
  }

  bool AutoFireButtonIn::update() {
    // Update the LEDs' brightness
    this->_led->update();

    if (this->_autoFireSelect->update()) {
      this->updateAutoFireState();
    }

    if (this->_pot->update()) {
      this->updateAutoFireRate();
    }

    this->updateButtonPress();

    // If the logical state of the button press has changed, indicate it
    return this->isLogicalStateChanged();
  }

  bool AutoFireButtonIn::read() {
    return this->_isLogicallyDown;
  }

  void AutoFireButtonIn::updateButtonPress() {
    if (this->_button->update()) {
      this->_logger->logln("physicallyPressed=", (this->_button->read() == LOW));
      this->setNewLogicalState(this->_button->read() == LOW);
      this->_timeSincePress_us = 0;

      // If autofire is selected and the button is no longer pressed
      if (this->isAutoFireSelected() && (this->_button->read() == HIGH)) {
        // Turn the led on incase the autofire had it set off
        this->_led->hardOn();
      }
    }
    // No button update and autofire is selected and button is phsically pressed
    else if (this->isAutoFireSelected() && (this->_button->read() == LOW)) {
      // Reset the time since to 0 and set the button to logically pressed
      if (this->_timeSincePress_us >= this->_autoFireTime_us) {
        this->_timeSincePress_us = 0;
        this->setNewLogicalState(true);
        this->_led->hardOn();
      }
      // If half of the time of the autofire repeat has passed and the button is still logically down
      else if ((this->_timeSincePress_us >= (this->_autoFireTime_us / 2)) && this->read()) {
        // Set it to logically unpressed
        this->setNewLogicalState(false);
        this->_led->hardOff();
      }
    }
    // No button update and autofire is not selected
    else {
      this->_wasLogicallyDown = this->_isLogicallyDown;
    }
  }

  void AutoFireButtonIn::updateAutoFireState() {
    if (this->_autoFireSelect->read() == LOW) {
      this->_logger->logln("autoFireOn");
      this->_led->softOn(ledSelectTimeMs);
      this->_timeSincePress_us = 0;
    }
    else {
      this->_logger->logln("autoFireOff");
      this->_led->softOff(ledDeselectTimeMs);
      this->setNewLogicalState((this->_button->read() == LOW));
    }
  }

  void AutoFireButtonIn::updateAutoFireRate() {
    uint16_t potVal = this->_pot->read();
    this->_autoFireTime_us = calculateAutoFireTime_us(potVal);
    this->_logger->logln(
      "autoFirePotVal=", potVal, " ",
      "autoFireTime_us=", this->_autoFireTime_us
    );
  }

  void AutoFireButtonIn::setNewLogicalState(bool isDown) {
    this->_logger->logln("logicallyPressed=", isDown);
    this->_wasLogicallyDown = this->_isLogicallyDown;
    this->_isLogicallyDown = isDown;
  }

  bool AutoFireButtonIn::isLogicalStateChanged() {
    return (this->_isLogicallyDown != this->_wasLogicallyDown);
  }

  bool AutoFireButtonIn::isAutoFireSelected() {
    return (this->_autoFireSelect->read() == LOW);
  }

  /**
   * Calculate the time between logical button presses when auto-fire is
   * selected.
   *
   * @parm potVal - Value read from the pot, range is from 0-63 (6 bits)
   * @return - Number of microseconds between auto-fire button presses.
   */
  unsigned long AutoFireButtonIn::calculateAutoFireTime_us(uint16_t potVal) {
    static double coef = -500000.0/63.1;
    double x = double(potVal);
    return (unsigned long) round((coef * x) + 500000.0);
  }
}
