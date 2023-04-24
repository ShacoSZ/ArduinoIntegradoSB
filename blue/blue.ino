#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial BTSerial(11, 10); // RX, TX
vexMotor motorLeft(3); // pinPWM del motor izquierdo
vexMotor motorRight(5); // pinPWM del motor derecho
int joyX, joyY; // valores de entrada del joystick
int prevJoyX = 0, prevJoyY = 0; // valores anteriores del joystick


void setup() {
    BTSerial.flush();
    delay(500);
    BTSerial.begin(38400); 
    Serial.begin(9600);
    Serial.println("Iniciando Torre ... ");
    delay(100);
    motorLeft.setup();
    motorRight.setup();

}

void loop(){
    int joyX = analogRead(A0);
    int joyY = analogRead(A1);
    Serial.print("x: ");
    Serial.println(joyX);
    Serial.print("y: ");
    Serial.println(joyY);
    if (joyX != prevJoyX || joyY != prevJoyY) {
        BTSerial.print("X:");
        BTSerial.print(joyX);
        BTSerial.print(",Y:");
        BTSerial.println(joyY);
        prevJoyX = joyX;
        prevJoyY = joyY;
    }

}