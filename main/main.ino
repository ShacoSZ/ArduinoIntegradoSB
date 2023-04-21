#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "SensorInfrarojo.h"
#include "Sonido.h"
//#include "voltaje.h"
//#include "vexMotor.h"
#include <DHT.h>
#include "Distancia.h"
#include "pir.h"
#include "voltajesensor.h"
//#include "temperatura.h"
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

/************** Ultrasonico **************/
  Distancia us1 = Distancia(22, 23, 0);
  const int numeroUS1 = 1; 

/************** Ultrasonico **************/
  Distancia us2 = Distancia(24, 25, 0);
  const int numeroUS2 = 1;   

SoftwareSerial HM10(2, 3); // RX, TX
int carritoX, carritoY;

StaticJsonDocument<200> doc;
JsonArray sensores = doc.to<JsonArray>();

void setup() {
  Serial.begin(9600);
  //HM10.begin(9600);
}

void loop() {

    //Logica de sensores
    JsonObject ultrasonico1 = sensores.createNestedObject();
    ultrasonico1["clave"] = "ult0";
    ultrasonico1["dato"] = us1.read();
    
    JsonObject ultrasonico2 = sensores.createNestedObject();
    ultrasonico2["clave"] = "ult1";
    ultrasonico2["dato"] = us2.read();

    JsonObject sonido = sensores.createNestedObject();
    sonido["clave"] = "son0";
    sonido["dato"] = sound1.read();

    JsonObject temperaturasao = sensores.createNestedObject();
    temperaturasao["clave"] = "tem0";
    temperaturasao["dato"] = Temperatura(9,0);

    JsonObject humedadsao = sensores.createNestedObject();
    humedadsao["clave"] = "hum0";
    humedadsao["dato"] = Humedad(9,0);

    JsonObject bateria1 = sensores.createNestedObject();
    bateria1["clave"] = "bat0";
    bateria1["dato"] = volt1.read();

    JsonObject PIR01 = sensores.createNestedObject();
    PIR01["clave"] = "pir0";
    PIR01["dato"] = mov1.read();

    JsonObject PIR02 = sensores.createNestedObject();
    PIR02["clave"] = "pir1";
    PIR02["dato"] = mov2.read();

    JsonObject infrarojo01 = sensores.createNestedObject();
    infrarojo01["clave"] = "ifr0";
    infrarojo01["dato"] = infrarojo1.read();

    JsonObject infrarojo02 = sensores.createNestedObject();
    infrarojo02["clave"] = "ifr1";
    infrarojo02["dato"] = infrarojo2.read();

    JsonObject Sensor_Gas0 = sensores.createNestedObject();
    Sensor_Gas0["clave"] = "gas0";
    Sensor_Gas0["dato"] = gas0.read();

    char jsonBuffer[512];
    serializeJson(doc,jsonBuffer,sizeof(jsonBuffer));
    Serial.println(jsonBuffer);
  
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