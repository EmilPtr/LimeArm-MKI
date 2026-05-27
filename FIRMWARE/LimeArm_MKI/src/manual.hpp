#ifndef MANUAL_HPP
#define MANUAL_HPP

#include <Arduino.h>

enum ManualAction {
  MANUAL_ACTION_NONE,
  MANUAL_ACTION_TOGGLE_TURRET,
  MANUAL_ACTION_TOGGLE_CLAW
};

struct ManualButton {
  bool lastReading;
  bool stableState;
  unsigned long lastDebounceTime;
  unsigned long firstPressTime;
  int pressCount;
};

void manualButtonInit(ManualButton &button, bool releasedState);
ManualAction manualButtonUpdate(ManualButton &button,
                                bool reading,
                                unsigned long now,
                                unsigned long debounceMs,
                                unsigned long doublePressMs);

#endif // MANUAL_HPP
