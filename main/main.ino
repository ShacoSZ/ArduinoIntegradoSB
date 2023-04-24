#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "SensorInfrarojo.h"
#include "Sonido.h"
#include "vexMotor.h"
#include <DHT.h>
#include "Distancia.h"
#include "pir.h"
#include "voltajesensor.h"
#include "Gas.h"

/************* Sensor Gas ***************/
  Sens_Gas gas0 = Sens_Gas(10,0);
  const int numero_gas0 = 1;

/************* Sensor Sonido **************/
  Sonido sound1 = Sonido(6,0);
  const int numero_sound = 1;

/************* Sensor Infrarojo IZQ **************/
  SensorInfrarojo infrarojo1 = SensorInfrarojo(7,0);
  const int numero_infrarojo1 = 1;

/************* Sensor Infrarojo DRCH **************/
  SensorInfrarojo infrarojo2 = SensorInfrarojo(8,0);
  const int numero_infrarojo2 = 1;

/************* Sensor PIR Frontal *************/
  Pir mov1 = Pir(4, 0);
  const int numeroMov1 = 1;

  /************* Sensor PIR Trasero *************/
  Pir mov2 = Pir(2, 0);
  const int numeroMov2 = 1;

/************ Voltaje_Sensor ****************/  
  voltajesensor volt1 = voltajesensor(A8,0);
  const int numero_volt = 1;


/************ Voltaje_Sensor ****************/  
  voltajesensor volt2 = voltajesensor(A9,0);
  const int numero_volt2 = 1;

/************** Ultrasonico **************/
  Distancia us1 = Distancia(22, 23, 0);
  const int numeroUS1 = 1; 

/************** Ultrasonico **************/
  Distancia us2 = Distancia(24, 25, 0);
  const int numeroUS2 = 1;   



StaticJsonDocument<200> doc;
JsonArray sensores = doc.to<JsonArray>();

SoftwareSerial BTSerial(11, 10); // RX, TX
int carritoX, carritoY;

vexMotor motorLeft(3); // pinPWM del motor izquierdo
vexMotor motorRight(5); // pinPWM del motor derecho

void setup() {
  BTSerial.flush();
  delay(500);
  BTSerial.begin(38400); 
  Serial.begin(9600);
  Serial.println("Iniciando ... ");
  delay(100);
  motorLeft.setup();
  motorRight.setup();

}

void loop() {
    String receivedData = ""; // variable para almacenar la cadena recibida
    int joyX, joyY; // variables para almacenar los valores de joyX y joyY

    if (BTSerial.available()) { // verifica si hay valoress disponibles en la conexión Bluetooth
      receivedData = BTSerial.readString(); // lee la cadena de caracteres enviada por el maestro
      // extrae los valores de joyX y joyY de la cadena recibida
      joyX = receivedData.substring(receivedData.indexOf(":")+1, receivedData.indexOf(",")).toInt();
      joyY = receivedData.substring(receivedData.lastIndexOf(":")+1, receivedData.length()-1).toInt();
      Serial.print("X: ");
      Serial.print(joyX);
      Serial.print(" Y: ");
      Serial.println(joyY);

      motores(joyX, joyY);
    }
    else{
      Serial.println("No hay datos");
      //sensores();
    }

      
}
void motores(int x, int y){
  int joyX = x;
  int joyY = y;
  if ((us1.read() < 10 && us2.read() < 10)||(infrarojo1.read() < 1 && infrarojo2.read() < 1))//se regresa poco
    {
      motorLeft.setSpeed(0);
      motorRight.setSpeed(0);
      delay(200);
    }
    else if (us1.read() < 10 || infrarojo1.read() == 1) //se regresa atras con el lado del sensor con mas potencia que el otro
    {
      motorLeft.setSpeed(0);
      motorRight.setSpeed(0);
      delay(200);

    }
    else if (us2.read() < 10 || infrarojo2.read() == 1) //gira al otor
    {
      motorLeft.setSpeed(0);
      motorRight.setSpeed(0);
      delay(200);
    }
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

}

void sensores(){
  //Logica de sensores
    JsonObject ultrasonico1;
    ultrasonico1["clave"] = "Ult0";
    float data = us1.read();
    if (data > 0){
      ultrasonico1["valores"] = data;
    }
    else{
      ultrasonico1["valores"] = 0;
    }
    ultrasonico1["valores"] = data;
    char jsonBuffer[512];
    serializeJson(ultrasonico1, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);
    
    JsonObject ultrasonico2;
    ultrasonico2["clave"] = "Ult1";
    float data2 = us2.read();
    if (data2 > 0){
      ultrasonico2["valores"] = data2;
    }
    else{
      ultrasonico2["valores"] = 0;
    }
    char jsonBuffer[512];
    serializeJson(ultrasonico2, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);


    JsonObject sonido;
    sonido["clave"] = "Son0";
    sonido["valores"] = sound1.read();
    char jsonBuffer[512];
    serializeJson(sonido, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);


    JsonObject temperaturasao;
    temperaturasao["clave"] = "Tem0";
    temperaturasao["valores"] = Temperatura(9,0);
    char jsonBuffer[512];
    serializeJson(temperaturasao, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);


    JsonObject humedadsao;
    humedadsao["clave"] = "Hum0";
    humedadsao["valores"] = Humedad(9,0);
    char jsonBuffer[512];
    serializeJson(humedadsao, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);


    JsonObject bateria1;
    bateria1["clave"] = "Bat0";
    bateria1["valores"] = volt1.read();
    char jsonBuffer[512];
    serializeJson(bateria1, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);

    JsonObject bateria2;
    bateria1["clave"] = "Bat1";
    bateria1["valores"] = volt1.read();
    char jsonBuffer[512];
    serializeJson(bateria1, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);


    JsonObject PIR01;
    PIR01["clave"] = "Pir0";
    PIR01["valores"] = mov1.read();
    char jsonBuffer[512];
    serializeJson(PIR01, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);

    JsonObject PIR02;
    PIR02["clave"] = "Pir1";
    PIR02["valores"] = mov2.read();
    char jsonBuffer[512];
    serializeJson(PIR02, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);

    JsonObject infrarojo01;
    infrarojo01["clave"] = "Ifr0";
    infrarojo01["valores"] = infrarojo1.read();
    char jsonBuffer[512];
    serializeJson(infrarojo01, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);

    JsonObject infrarojo02;
    infrarojo02["clave"] = "Ifr1";
    infrarojo02["valores"] = infrarojo2.read();
    char jsonBuffer[512];
    serializeJson(infrarojo02, jsonBuffer, sizeof(jsonBuffer));
    BTSerial.print(jsonBuffer);

    JsonObject Sensor_Gas0;
    Sensor_Gas0["clave"] = "Gas0";
    Sensor_Gas0["valores"] = gas0.read();
    char jsonBuffer


}


int Temperatura(int _pin, int _numero) {
  int pin = _pin;
  int numero = _numero;
  #define DHTPIN pin    // Pin donde está conectado el sensor
  #define DHTTYPE DHT11
  DHT temp(pin, DHTTYPE);
  temp.begin();

  float temperatura = temp.readTemperature();
  delay(1000);
  return temperatura;
}

int Humedad(int _pin, int _numero) {
  int pin = _pin;
  int numero = _numero;
  #define DHTPIN pin    // Pin donde está conectado el sensor
  #define DHTTYPE DHT11
  DHT temp(pin, DHTTYPE);
  temp.begin();

  float humedad = temp.readHumidity();
  delay(1000);
  return humedad;
}