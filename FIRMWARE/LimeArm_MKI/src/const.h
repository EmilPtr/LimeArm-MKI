#ifndef CONSTANTS_H
#define CONSTANTS_H

// Stepper motor constants
#define STEP_FB_PIN 16, 18, 17, 19
#define STEP_UD_PIN 2, 12, 4, 14
#define STEP_TURR_PIN 32, 26, 33, 27
#define STEP_MAX_ACCEL 30
#define STEP_MAX_SPEED 100

// Claw pin constants
#define CLAW_PIN 25
#define CLAW_PULSE_HERTZ 50
#define CLAW_PULSE_MIN 500
#define CLAW_PULSE_MAX 2400

// Control constants
#define MANUAL_MODE true
#define JOY_X_PIN 34
#define JOY_Y_PIN 35
#define JOY_DEADZONE 350
#define JOY_SWITCH_PIN 13

#endif // CONSTANTS_H