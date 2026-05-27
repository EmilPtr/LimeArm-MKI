#include <Arduino.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>
#include "const.h"

Servo clawServo;
AccelStepper stepFB(AccelStepper::FULL4WIRE, STEP_FB_PIN);
AccelStepper stepUD(AccelStepper::FULL4WIRE, STEP_UD_PIN);

void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  clawServo.setPeriodHertz(50);
  clawServo.attach(25, 500, 2400);

  stepFB.setMaxSpeed(100);
  stepFB.setAcceleration(50);
  stepFB.setCurrentPosition(0);

  stepUD.setMaxSpeed(100);
  stepUD.setAcceleration(50);
  stepUD.setCurrentPosition(0);
}

void loop() {
  static unsigned long lastSpeedPrint = 0;

  int xValue = analogRead(JOY_X_PIN);
  int yValue = analogRead(JOY_Y_PIN);

  int xSpeed = map(xValue, 0, 4095, -STEP_MAX_SPEED, STEP_MAX_SPEED);
  int ySpeed = map(yValue, 0, 4095, -STEP_MAX_SPEED, STEP_MAX_SPEED);

  if (abs(xValue - 1850) < JOY_DEADZONE) {
    xSpeed = 0;
  }
  if (abs(yValue - 1850) < JOY_DEADZONE) {
    ySpeed = 0;
  }

  if (millis() - lastSpeedPrint >= 100) {
    lastSpeedPrint = millis();
    Serial.print("xSpeed: ");
    Serial.print(xSpeed);
    Serial.print(" ySpeed: ");
    Serial.println(ySpeed);
  }

  stepFB.setSpeed(xSpeed);
  stepFB.runSpeed();

  stepUD.setSpeed(ySpeed);
  stepUD.runSpeed();

  
}
