#ifndef CONSTANTS_H
#define CONSTANTS_H

// Stepper motor constants
#define STEP_FB_PIN 16, 18, 17, 19
#define STEP_UD_PIN 2, 12, 4, 14
#define STEP_TURR_PIN 32, 26, 33, 27
#define STEP_MAX_ACCEL 110
#define STEP_MAX_SPEED 200
#define STEP_TURRET_MAX_ACCEL 600
#define STEP_TURRET_MAX_SPEED 1200

// Claw pin constants
#define CLAW_PIN 25
#define CLAW_PULSE_HERTZ 50
#define CLAW_PULSE_MIN 500
#define CLAW_PULSE_MAX 2400
#define CLAW_CLOSED_ANGLE 90
#define CLAW_OPEN_ANGLE 180

// Control constants
#define MANUAL_MODE true
#define JOY_X_PIN 34
#define JOY_Y_PIN 35
#define JOY_CENTER 1850
#define JOY_DEADZONE 350
#define JOY_SWITCH_PIN 13
#define BUTTON_DEBOUNCE_MS 35
#define BUTTON_DOUBLE_PRESS_MS 300

#endif // CONSTANTS_H
