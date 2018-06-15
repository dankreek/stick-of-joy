#ifndef PWMLED_H
#define PWMLED_H

#include <Arduino.h>
#include <cstdint>

namespace dankreek {

  class PwmLed {
  protected:
    void initInstance(uint8_t pin);

    static const uint32_t DEFAULT_ANALOG_WRITE_RESOLUTION = 8;
    uint8_t _pinNum;
    uint16_t _brightness;

  public:
    static const uint32_t ANALOG_WRITE_RESOLUTION = 8;

    // Initialize the Teensy's PWM output functionality
    static void init();

    // Create a new PWM LED controller with the LED on the given pin number.
    // @param pinNum    - The LED's pin number
    // @param frequency (optional) - PWM frequency for analog writes to this pin
    PwmLed(uint8_t pinNum, float frequency);
    PwmLed(uint8_t pinNum);

    // Set and get the LED brightness
    void setBrightness(uint16_t brightness);
    uint16_t getBrightness();
  };
}
#endif
