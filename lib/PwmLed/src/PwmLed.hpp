#ifndef PWMLED_H
#define PWMLED_H

#include <Arduino.h>
#include <cstdint>

namespace dankreek {

class PwmLed {
protected:
  void initInstance(uint8_t pin);
  void setBrightness(uint16_t brightness);
  void handleGradientChange();
  void handleOscillateChange();

  enum AnimationMode {
    gradient, oscillating, stopped
  };

  static const uint32_t DEFAULT_ANALOG_WRITE_RESOLUTION = 8;
  // XXX: use ellapsedMicros for precision
  elapsedMicros _timer;
  uint8_t _pinNum;
  uint16_t _brightness;

  // Used for animation calculations
  AnimationMode _mode;
  uint16_t _startBrightness;
  uint16_t _endBrightness;
  uint32_t _animTimeUs; // Total amount of time in an animation
  uint16_t _numCycles;
  uint16_t _animCycleCount;
  double _changeRate;

public:
  static const uint32_t ANALOG_WRITE_RESOLUTION = 8;

  // Initialize the Teensy's PWM output functionality
  static void init();

  // Create a new PWM LED controller with the LED on the given pin number.
  // @param pinNum    - The LED's pin number
  // @param frequency (optional) - PWM frequency for analog writes to this pin
  PwmLed(uint8_t pinNum, float frequency);
  PwmLed(uint8_t pinNum);

  // Poll to update brightness during animations
  void update();

  // Set a constant brightness, cancel all animations
  void constant(uint16_t brightness);

   // Runs a brightness gradient from the initial brightness to the final
   // brightness in the given number of milliseconds. The LED will remain at the
   // final brightness after the gradient has run.
  void startGradient(uint16_t initBrightness, uint16_t finalBrightness, uint16_t timeMS);

   // Oscillate between the specified minimum and maximum brightness. The time
   // is the amount of time (in milliseconds) for a full cycle.
   //
   // If the number of cycles is specified the oscillation will be set to the
   // final brightness after the cycles have ended.
  void oscillate(uint16_t minBrightness, uint16_t maxBrightness, uint16_t timeMS);
  void oscillate(
    uint16_t min_brightness, uint16_t max_brightness, uint16_t time_ms,
    uint16_t num_cycles, uint16_t final_brightness
  );
};
}
#endif
