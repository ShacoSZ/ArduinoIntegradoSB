#include "vexMotor.h"
#include <SoftwareSerial.h>

vexMotor motorLeft(38); // pinPWM del motor izquierdo
vexMotor motorRight(39); // pinPWM del motor derecho
SoftwareSerial BTSerial(11, 10); // RX, TX
String data; // variable para almacenar los datos recibidos
int joyX  = 509, joyY = 504; // variables para almacenar los valores x e y


void setup() {
  // inicialización de los objetos vexMotor
 BTSerial.flush();
  delay(500);
  BTSerial.begin(38400); 
  Serial.begin(9600);
  Serial.println("Iniciando Carrito... ");
    BTSerial.print("Hola torre");
  delay(100);
  motorLeft.setup();
  motorRight.setup();
}

void loop() {
while(BTSerial.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    data = BTSerial.readStringUntil('\n');
    // busca la posición de la coma en la cadena
    int commaPos = data.indexOf(',');
    if (commaPos != -1) { // si se encuentra la coma
    // obtiene la subcadena antes de la coma y la convierte a un entero
    joyX = data.substring(0, commaPos).toInt();
    // obtiene la subcadena después de la coma y la convierte a un entero
    joyY = data.substring(commaPos + 1).toInt();
    // imprime los valores de x e y en la consola serial
    Serial.print("x = ");
    Serial.print(joyX);
    Serial.print(", y = ");
    Serial.println(joyY);
    // mapear la entrada del joystick a la velocidad del motor
    int motorLeftSpeed = map(joyY,  0, 1025, 0, 100)+3;
    int motorRightSpeed = map(joyY, 0, 1025,  0, 100)+1;
    int turningSpeed = map(joyX, 0, 1025, -40, 40);

    motorLeftSpeed += turningSpeed;
    motorRightSpeed -= turningSpeed;

   /* if (motorLeftSpeed >= 100){
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
    }*/

    motorLeft.setSpeed(motorLeftSpeed);
    motorRight.setSpeed(motorRightSpeed);
    Serial.println(motorLeftSpeed);
    Serial.println(motorRightSpeed);
  }


delay(500);


  //74 punto medio
  //33 punto menor
  //99 punto mayor
}
}

