#include "manual.hpp"

void manualButtonInit(ManualButton &button, bool releasedState) {
  button.lastReading = releasedState;
  button.stableState = releasedState;
  button.lastDebounceTime = 0;
  button.firstPressTime = 0;
  button.pressCount = 0;
}

ManualAction manualButtonUpdate(ManualButton &button,
                                bool reading,
                                unsigned long now,
                                unsigned long debounceMs,
                                unsigned long doublePressMs) {
  if (reading != button.lastReading) {
    button.lastDebounceTime = now;
  }

  if (now - button.lastDebounceTime >= debounceMs && reading != button.stableState) {
    button.stableState = reading;

    // INPUT_PULLUP means LOW is a pressed button.
    if (button.stableState == LOW) {
      button.pressCount++;

      if (button.pressCount == 1) {
        button.firstPressTime = now;
      } else if (button.pressCount == 2) {
        button.pressCount = 0;
        button.lastReading = reading;
        return MANUAL_ACTION_TOGGLE_CLAW;
      }
    }
  }

  button.lastReading = reading;

  if (button.pressCount == 1 && now - button.firstPressTime > doublePressMs) {
    button.pressCount = 0;
    return MANUAL_ACTION_TOGGLE_TURRET;
  }

  return MANUAL_ACTION_NONE;
}
