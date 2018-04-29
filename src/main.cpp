#include <Arduino.h>
#include <PwmLed.hpp>
#include <Pot.hpp>
#include <JoystickOut.hpp>
#include <IInputButton.hpp>
#include <InputButton.hpp>
#include <DebouncedInputButton.hpp>
#include <Logger.hpp>
#include "input/JoystickIn.hpp"
#include "input/FireButtonsIn.hpp"
#include "input/ModeSelectorsIn.hpp"
#include "modes/PlatformGameMode.hpp"
#include "InputRouter.hpp"

#define STICK_DEBOUNCE 2
#define FIRE_DEBOUNCE 2
#define MODE_DEBOUNCE 2

using namespace dankreek;

DebouncedInputButton up = DebouncedInputButton(3, STICK_DEBOUNCE);
DebouncedInputButton down = DebouncedInputButton(2, STICK_DEBOUNCE);
DebouncedInputButton left = DebouncedInputButton(0, STICK_DEBOUNCE);
DebouncedInputButton right = DebouncedInputButton(1, STICK_DEBOUNCE);
DebouncedInputButton a = DebouncedInputButton(10, FIRE_DEBOUNCE);
DebouncedInputButton b = DebouncedInputButton(11, FIRE_DEBOUNCE);

DebouncedInputButton mode1 = DebouncedInputButton(24, MODE_DEBOUNCE);
DebouncedInputButton mode2 = DebouncedInputButton(25, MODE_DEBOUNCE);
DebouncedInputButton mode3 = DebouncedInputButton(26, MODE_DEBOUNCE);
DebouncedInputButton joyOutSelect = DebouncedInputButton(27, MODE_DEBOUNCE);

OutputButton joy1up = OutputButton(28);
OutputButton joy1down = OutputButton(27);
OutputButton joy1left = OutputButton(26);
OutputButton joy1right = OutputButton(25);
OutputButton joy1fire = OutputButton(24);

OutputButton joy2up = OutputButton(39);
OutputButton joy2down = OutputButton(38);
OutputButton joy2left = OutputButton(37);
OutputButton joy2right = OutputButton(36);
OutputButton joy2fire = OutputButton(35);
DebouncedInputButton autoFireSelectA = DebouncedInputButton(21, MODE_DEBOUNCE);
DebouncedInputButton autoFireSelectB = DebouncedInputButton(20, MODE_DEBOUNCE);

PwmLed autoFireALed = PwmLed(5);
PwmLed autoFireBLed = PwmLed(6);
PwmLed joy1SelectLed = PwmLed(7);
PwmLed joy2SelectLed = PwmLed(8);

Pot autoFireAPot = Pot(9);
Pot autoFireBPot = Pot(8);

/*******************************************************************************
 * Input modules
 **/

JoystickIn joystickIn = JoystickIn(up, down, left, right);

FireButtonsIn fireButtonsIn = FireButtonsIn(
  a, b,
  autoFireALed, autoFireBLed,
  autoFireAPot, autoFireBPot,
  autoFireSelectA, autoFireSelectB
);

ModeSelectorsIn modeSelectorsIn = ModeSelectorsIn(
  mode1, mode2, mode3, joyOutSelect
);

/*******************************************************************************
 * Output modules
 **/

JoystickOut joystick1Out = JoystickOut(
  joy1up, joy1down, joy1left, joy1right, joy1fire
);

JoystickOut joystick2Out = JoystickOut(
  joy2up, joy2down, joy2left, joy2right, joy2fire
);

/*******************************************************************************
 * Modes
 **/

PlatformGameMode platformMode = PlatformGameMode(joystick1Out, joystick2Out);

/*******************************************************************************
 * Input router
 **/
InputRouter inputRouter = InputRouter(
  joystick1Out, joystick2Out,
  platformMode
);

void setup() {
  Logger::init();
  // PwmLed::init();
  // Pot::init();
}

void loop() {
  modeSelectorsIn.update(inputRouter);
  joystickIn.update(inputRouter);
  fireButtonsIn.update(inputRouter);
}
