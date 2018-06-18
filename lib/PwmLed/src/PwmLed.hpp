#ifndef PWMLED_H
#define PWMLED_H

#include <Arduino.h>
#include <cstdint>

namespace dankreek {

  class PwmLed {
    typedef uint16_t ledBrightness;

  public:
    static const uint32_t ANALOG_WRITE_RESOLUTION = 8;

    // Initialize the Teensy's PWM output functionality
    static void init();

    // Create a new PWM LED controller with the LED on the given pin number.
    // @param pinNum    - The LED's pin number
    // @param maxBrightness - PWM duty cycle which is considerd
    //                        the LED's maximum brightness
    PwmLed(uint8_t pinNum, ledBrightness maxBrightness);

    void softOff(uint16_t transitionTimeMs);
    void softOn(uint16_t transitionTimeMs);
    void hardOff();
    void hardOn();

    // Update the state of the transition effects
    void update();

  protected:
    static const uint32_t DEFAULT_ANALOG_WRITE_RESOLUTION = 8;

    void setBrightness(ledBrightness brightness);
    void startTransition(uint16_t transitionTimeMs, bool isIncreasing);
    void stopTransition();
    bool isTransitionRunning();
    bool isNextStepTime();

    uint8_t _pinNum;
    ledBrightness _curBrightness;
    ledBrightness _maxBrightness;
    elapsedMicros _timeSinceLastStep;
    bool _isTransitionIncreasing;
    
    // The number of microseconds until the next step in brightness
    unsigned long _nextStepTime_us;

  };
}
#endif
