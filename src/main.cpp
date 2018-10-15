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

/*******************************************************************************
 * Basic input and output hardware definitions.
 * All the pins which hardware is attached to are defined here.
 */

// Joystick directions and fire buttons (momentary)
DebouncedInputButton up = DebouncedInputButton(3, STICK_DEBOUNCE);
DebouncedInputButton down = DebouncedInputButton(2, STICK_DEBOUNCE);
DebouncedInputButton left = DebouncedInputButton(0, STICK_DEBOUNCE);
DebouncedInputButton right = DebouncedInputButton(1, STICK_DEBOUNCE);
DebouncedInputButton a = DebouncedInputButton(10, FIRE_DEBOUNCE);
DebouncedInputButton b = DebouncedInputButton(11, FIRE_DEBOUNCE);

// Mode and joystick output selector buttons (momentary)
DebouncedInputButton mode1 = DebouncedInputButton(24, MODE_DEBOUNCE);
DebouncedInputButton mode2 = DebouncedInputButton(25, MODE_DEBOUNCE);
DebouncedInputButton mode3 = DebouncedInputButton(26, MODE_DEBOUNCE);
DebouncedInputButton joyOutSelect = DebouncedInputButton(27, MODE_DEBOUNCE);

// Joystick port outputs
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

// Auto-fire select buttons (push-button switches)
DebouncedInputButton autoFireSelectA = DebouncedInputButton(29, MODE_DEBOUNCE);
DebouncedInputButton autoFireSelectB = DebouncedInputButton(30, MODE_DEBOUNCE);

// LEDs
PwmLed autoFireALed = PwmLed(5, 0x18);
PwmLed autoFireBLed = PwmLed(6, 0x18);
PwmLed joy1SelectedLed = PwmLed(7, 0x18);
PwmLed joy2SelectedLed = PwmLed(8, 0x18);

// Auto-fire rate pots
//
// Note: on the Teensy (using Teensyduino) these pins are the analog pin numbers and not the digital pin numbers
Pot autoFireAPot = Pot(12);
Pot autoFireBPot = Pot(13);

/*******************************************************************************
 * Autofire input/output modules.
 *
 * These read the auto-fire on/off state, the auto-fire rate, and button
 * physical state which are then translated into logical button pushes
 * and sent to the input router.
 **/

AutoFireButtonIn autoFireA = AutoFireButtonIn(
  a, autoFireALed, autoFireAPot, autoFireSelectA, "AutoFireButtonIn:A"
);

AutoFireButtonIn autoFireB = AutoFireButtonIn(
  b, autoFireBLed, autoFireBPot, autoFireSelectB, "AutoFireButtonIn:B"
);

/*******************************************************************************
 * Joystick input modules
 **/

JoystickIn joystickIn = JoystickIn(up, down, left, right);
FireButtonsIn fireButtonsIn = FireButtonsIn(autoFireA, autoFireB);

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
 * Joystick output modes
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
 * Mode and joystick output selectors
 *
 * When modeSelectorsIn is updated, any change in mode is sent to the
 * input router.
 *
 * This module also has the responsibility of sending updates to the joystick
 * output selector LEDs. The input router doesn't directly manipulate these but
 * this relieves the output modes from all having to contain the same LED
 * update code.
 **/
ModeSelectorsIn modeSelectorsIn = ModeSelectorsIn(
  mode1, mode2, mode3, joyOutSelect,
  singleButtonMode, platformGameMode, dualOutMode,
  joy1SelectedLed, joy2SelectedLed
);

/*******************************************************************************
 * Input router
 *
 * All joystick directions and logical button pressed (sent from the
 * AutoFireSelect modules) are sent to the input router which then sends them
 * to the currently selected mode which determines which joystick outputs
 * to send them to.
 **/
InputRouter inputRouter = InputRouter(joystick1Out, joystick2Out);

void setup() {
  // Use built-in LED to signal that the setup has begun and ended.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Logger::init();
  PwmLed::init();
  Pot::init();

  // Set the initial output mode
  // if an initial output mode is not set then nothing will be output
  inputRouter.selectMode(&dualOutMode);

  // Setup is finished, turn off built-in LED
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Send output mode changes to the input router
  modeSelectorsIn.update(inputRouter);

  // Send joystick directions the input router
  joystickIn.update(inputRouter);

  // Send logical button presses from the auto fire modules to the input router
  fireButtonsIn.update(inputRouter);
}
