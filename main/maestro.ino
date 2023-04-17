#include <SoftwareSerial.h>
SoftwareSerial HM10Serial(2, 3); // RX, TX para HM-10
int xPin = A0; // Pin analógico para joystick x
int yPin = A1; // Pin analógico para joystick y
int xVal = 0; 
int yVal = 0; 
void setup() {
  Serial.begin(9600); 
  HM10Serial.begin(9600); 
}
void loop() {
  while (HM10Serial.available()) {
    char c = HM10Serial.read();
    Serial.write(c);
  }  
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  int xValScaled = map(xVal, 0, 1023, 0, 255);
  int yValScaled = map(yVal, 0, 1023, 0, 255);
  String joystickData = String(xValScaled) + "," + String(yValScaled) + "\n";
  HM10Serial.print(joystickData);
    delay(100);
}
