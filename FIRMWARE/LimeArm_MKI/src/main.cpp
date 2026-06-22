#include <Arduino.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>
#include "const.h"
#include "manual.hpp"

Servo clawServo;
AccelStepper stepFB(AccelStepper::FULL4WIRE, STEP_FB_PIN);
AccelStepper stepUD(AccelStepper::FULL4WIRE, STEP_UD_PIN);
AccelStepper stepTurr(AccelStepper::FULL4WIRE, STEP_TURR_PIN);

ManualButton joystickButton;
bool turretMode = false;
bool clawOpen = false;

void configureStepper(AccelStepper &stepper, int maxSpeed, int acceleration) {
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(acceleration);
  stepper.setCurrentPosition(0);
}

int joystickToSpeed(int value, int maxSpeed) {
  if (abs(value - JOY_CENTER) < JOY_DEADZONE) {
    return 0;
  }

  return map(value, 0, 4095, -maxSpeed, maxSpeed);
}

void handleManualAction(ManualAction action) {
  if (action == MANUAL_ACTION_TOGGLE_TURRET) {
    turretMode = !turretMode;
  } else if (action == MANUAL_ACTION_TOGGLE_CLAW) {
    clawOpen = !clawOpen;
    clawServo.write(clawOpen ? CLAW_OPEN_ANGLE : CLAW_CLOSED_ANGLE);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(JOY_SWITCH_PIN, INPUT_PULLUP);
  manualButtonInit(joystickButton, HIGH);

  // Servo setup stays here because the claw is directly controlled by main.
  ESP32PWM::allocateTimer(0);
  clawServo.setPeriodHertz(50);
  clawServo.attach(CLAW_PIN, CLAW_PULSE_MIN, CLAW_PULSE_MAX);
  clawServo.write(CLAW_CLOSED_ANGLE);

  configureStepper(stepFB, STEP_MAX_SPEED, STEP_MAX_ACCEL);
  configureStepper(stepUD, STEP_MAX_SPEED, STEP_MAX_ACCEL);
  configureStepper(stepTurr, STEP_TURRET_MAX_SPEED, STEP_TURRET_MAX_ACCEL);
}

void loop() {
  ManualAction buttonAction = manualButtonUpdate(joystickButton,
                                                 digitalRead(JOY_SWITCH_PIN),
                                                 millis(),
                                                 BUTTON_DEBOUNCE_MS,
                                                 BUTTON_DOUBLE_PRESS_MS);
  handleManualAction(buttonAction);

  int xValue = analogRead(JOY_X_PIN);
  int yValue = analogRead(JOY_Y_PIN);
  int xSpeed = joystickToSpeed(xValue, turretMode ? STEP_TURRET_MAX_SPEED : STEP_MAX_SPEED);
  int ySpeed = joystickToSpeed(yValue, STEP_MAX_SPEED);

  if (turretMode) {
    // Turret mode gives the X axis to rotation and ignores Y.
    stepFB.setSpeed(0);
    stepUD.setSpeed(0);
    stepTurr.setSpeed(xSpeed);
  } else {
    // Drive mode uses both joystick axes for the arm movement.
    stepFB.setSpeed(-xSpeed);
    stepUD.setSpeed(ySpeed);
    stepTurr.setSpeed(0);
  }

  stepFB.runSpeed();
  stepUD.runSpeed();
  stepTurr.runSpeed();
}
