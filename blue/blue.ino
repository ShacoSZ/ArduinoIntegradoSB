#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial BTSerial(10, 11); // Amarillo, Blanco
int joyX, joyY; // valores de entrada del joystick
int prevJoyX = 0, prevJoyY = 0; // valores anteriores del joystick

void setup() {
    BTSerial.flush();
    delay(500);
    BTSerial.begin(38400); 
    Serial.begin(9600);
    Serial.println("Iniciando Torre ... ");
    BTSerial.print("AT\r\n");
    delay(100);
}

void loop(){
    int joyX = analogRead(A0);
    int joyY = analogRead(A1);
    if ((joyX < prevJoyX - 2 || joyX > prevJoyX + 2) || (joyY < prevJoyY - 2 || joyY > prevJoyY + 2)) {
        String data = String(joyX) + "," + String(joyY);
        // Enviar la cadena de caracteres a través de la comunicación serial
        BTSerial.println(data);
        prevJoyX = joyX;
        prevJoyY = joyY;
        Serial.println("Mandando datos");
        delay(300);
    }
}