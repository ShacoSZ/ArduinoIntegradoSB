#include "vexMotor.h"

vexMotor motorLeft(3); // pinPWM del motor izquierdo
vexMotor motorRight(5); // pinPWM del motor derecho
 

void setup() {
  // inicialización de los objetos vexMotor
  motorLeft.setup();
  motorRight.setup();
  Serial.begin(9600);
  Serial.println("Inicio");
}

void loop() {
int joyX = analogRead(A0);
int joyY = analogRead(A1);

<<<<<<< HEAD

=======
>>>>>>> ee70a720436271f4c359c31d8ce129437107b36e
Serial.print("x: ");
Serial.println(joyX);
Serial.print("y: ");
Serial.println(joyY);

// mapear la entrada del joystick a la velocidad del motor
int motorLeftSpeed = map(joyY, -5, 755, 33, 115)+23;
int motorRightSpeed = map(joyY, -5, 755, 33, 115)-9;
int turningSpeed = map(joyX, 0, 1023, -40, 40);

motorLeftSpeed += turningSpeed;
motorRightSpeed -= turningSpeed;

if (motorLeftSpeed >= 100){
  motorLeftSpeed = 99;
}
if (motorRightSpeed >= 100){
  motorRightSpeed = 99;
}
if (motorLeftSpeed < 33){
  motorLeftSpeed = 33;
}
if (motorRightSpeed < 33){
  motorRightSpeed = 33;
}

motorLeft.setSpeed(motorLeftSpeed);
motorRight.setSpeed(motorRightSpeed);
Serial.println(motorLeftSpeed);
Serial.println(motorRightSpeed);

delay(500);


  //74 punto medio
  //33 punto menor
  //99 punto mayor
}

