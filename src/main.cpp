#include <Arduino.h>
#include <PwmLed.hpp>
#include <Pot.hpp>
#include <JoystickOut.hpp>
#include <IInputButton.hpp>
#include <InputButton.hpp>
#include <DebouncedInputButton.hpp>
#include <Logger.hpp>
#include "input/JoystickIn.hpp"
#include "input/AutoFireButtonIn.hpp"
#include "input/FireButtonsIn.hpp"
#include "input/ModeSelectorsIn.hpp"
#include "modes/PlatformGameMode.hpp"
#include "modes/SingleButtonMode.hpp"
#include "modes/DualOutMode.hpp"
#include "InputRouter.hpp"

#define STICK_DEBOUNCE 2
#define FIRE_DEBOUNCE 2
#define MODE_DEBOUNCE 3

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

OutputButton joy1up = OutputButton(18);
OutputButton joy1down = OutputButton(17);
OutputButton joy1left = OutputButton(16);
OutputButton joy1right = OutputButton(15);
OutputButton joy1fire = OutputButton(14);

OutputButton joy2up = OutputButton(39);
OutputButton joy2down = OutputButton(38);
OutputButton joy2left = OutputButton(37);
OutputButton joy2right = OutputButton(36);
OutputButton joy2fire = OutputButton(35);

DebouncedInputButton autoFireSelectA = DebouncedInputButton(29, MODE_DEBOUNCE);
DebouncedInputButton autoFireSelectB = DebouncedInputButton(30, MODE_DEBOUNCE);

PwmLed autoFireALed = PwmLed(5, 0x60);
PwmLed autoFireBLed = PwmLed(6, 0x60);
PwmLed joy1SelectedLed = PwmLed(7, 0x60);
PwmLed joy2SelectedLed = PwmLed(8, 0x60);

Pot autoFireAPot = Pot(12);
Pot autoFireBPot = Pot(13);

AutoFireButtonIn autoFireA = AutoFireButtonIn(
  a, autoFireALed, autoFireAPot, autoFireSelectA, "AutoFireButtonIn:A"
);

AutoFireButtonIn autoFireB = AutoFireButtonIn(
  b, autoFireBLed, autoFireBPot, autoFireSelectB, "AutoFireButtonIn:B"
);

/*******************************************************************************
 * Input modules
 **/

JoystickIn joystickIn = JoystickIn(up, down, left, right);

FireButtonsIn fireButtonsIn = FireButtonsIn(autoFireA, autoFireB);

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

PlatformGameMode platformGameMode = PlatformGameMode(
  joystick1Out, joystick2Out,
  joy1SelectedLed, joy2SelectedLed
);

SingleButtonMode singleButtonMode = SingleButtonMode(
  joystick1Out, joystick2Out,
  joy1SelectedLed, joy2SelectedLed
);

DualOutMode dualOutMode = DualOutMode(
  joystick1Out, joystick2Out,
  joy1SelectedLed, joy2SelectedLed
);


/*******************************************************************************
 * Input router
 **/

InputRouter inputRouter = InputRouter(
  joystick1Out, joystick2Out,
  platformGameMode, singleButtonMode, dualOutMode
);

void setup() {
  // Use built-in LED to signal that the setup has begun and ended.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Logger::init();
  PwmLed::init();
  Pot::init();
  inputRouter.init();

  // Setup is finished, turn off built-in LED
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  modeSelectorsIn.update(inputRouter);
  joystickIn.update(inputRouter);
  fireButtonsIn.update(inputRouter);

  // This seems a little out of place, but updating the joy select LED's
  // outside of the mode classes is DRYer
  joy1SelectedLed.update();
  joy2SelectedLed.update();
}
