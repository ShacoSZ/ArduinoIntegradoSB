#ifndef vexMotor_H
#define vexMotor_H
#include <Arduino.h>

class vexMotor {
  private:
    int pinPWM;

  public:
    vexMotor(int pinPWM);
    void setup();
    void setSpeed(int speed);
};


#endif