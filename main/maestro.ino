#include <SoftwareSerial.h>
SoftwareSerial HM10(2, 3); // RX, TX
int joystickX, joystickY;
void setup() {
  Serial.begin(9600);
  HM10.begin(9600);
}
void loop() {
  joystickX = analogRead(A0);
  joystickY = analogRead(A1);
  String joystickData = "J:" + String(joystickX) + "," + String(joystickY) + "\n";
  HM10.print(joystickData);
  if (HM10.available()) {
    String balizaData = HM10.readString();
    Serial.print("Enviando datos de la baliza a la Raspberry Pi: ");
    Serial.println(balizaData);
    Serial1.print(balizaData);
  }
}
