#include "vexMotor.h"

vexMotor::vexMotor(int pinPWM) {
  pinPWM = pinPWM;
}

void vexMotor::setup() {
  pinMode(pinPWM, OUTPUT);
}

void vexMotor::setSpeed(int speed) {
  if (speed > 100) {
    speed = 100;
  } else if (speed < -100) {
    speed = -100;
  }

  int pwmValue = map(speed, -100, 100, -255, 255);
  analogWrite(pinPWM, abs(pwmValue));
  digitalWrite(pinPWM + 1, pwmValue < 0 ? HIGH : LOW);
}

