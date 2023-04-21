#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "SensorInfrarojo.h"
#include "Sonido.h"
//#include "voltaje.h"
#include "vexMotor.h"
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
vexMotor motorLeft(3); // pinPWM del motor izquierdo
vexMotor motorRight(5); // pinPWM del motor derecho

void setup() {
  BTSerial.flush();
  delay(500);
  BTSerial.begin(38400); 
  Serial.begin(9600);
  Serial.println("Iniciando ... ");
  BTSerial.print("AT\r\n");
  delay(100);

  //HM10.begin(9600);
  motorLeft.setup();
  motorRight.setup();
}

void loop() {
    String receivedData = ""; // variable para almacenar la cadena recibida
    int joyX, joyY; // variables para almacenar los valores de joyX y joyY

    if (BTSerial.available()) { // verifica si hay datos disponibles en la conexión Bluetooth
      receivedData = BTSerial.readString(); // lee la cadena de caracteres enviada por el maestro
      // extrae los valores de joyX y joyY de la cadena recibida
      joyX = receivedData.substring(receivedData.indexOf(":")+1, receivedData.indexOf(",")).toInt();
      joyY = receivedData.substring(receivedData.lastIndexOf(":")+1, receivedData.length()-1).toInt();
    }
    else{
      joyX = 0;
      joyY = 0;
    }
    //tiene que estar quieto el carrito para poder mandar los datos
    if (joyX < 55 && joyX > 33 && joyY < 55 && joyY > 33){
      //Logica de sensores
      JsonObject ultrasonico1 = sensores.createNestedObject();
      ultrasonico1["clave"] = "Ult0";
      ultrasonico1["dato"] = us1.read();
      
      JsonObject ultrasonico2 = sensores.createNestedObject();
      ultrasonico2["clave"] = "Ult1";
      ultrasonico2["dato"] = us2.read();

      JsonObject sonido = sensores.createNestedObject();
      sonido["clave"] = "Son0";
      sonido["dato"] = sound1.read();

      JsonObject temperaturasao = sensores.createNestedObject();
      temperaturasao["clave"] = "Tem0";
      temperaturasao["dato"] = Temperatura(9,0);

      JsonObject humedadsao = sensores.createNestedObject();
      humedadsao["clave"] = "Hum0";
      humedadsao["dato"] = Humedad(9,0);

      JsonObject bateria1 = sensores.createNestedObject();
      bateria1["clave"] = "Bat0";
      bateria1["dato"] = volt1.read();

      JsonObject PIR01 = sensores.createNestedObject();
      PIR01["clave"] = "Pir0";
      PIR01["dato"] = mov1.read();

      JsonObject PIR02 = sensores.createNestedObject();
      PIR02["clave"] = "Pir1";
      PIR02["dato"] = mov2.read();

      JsonObject infrarojo01 = sensores.createNestedObject();
      infrarojo01["clave"] = "Ifr0";
      infrarojo01["dato"] = infrarojo1.read();

      JsonObject infrarojo02 = sensores.createNestedObject();
      infrarojo02["clave"] = "Ifr1";
      infrarojo02["dato"] = infrarojo2.read();

      JsonObject Sensor_Gas0 = sensores.createNestedObject();
      Sensor_Gas0["clave"] = "Gas0";
      Sensor_Gas0["dato"] = gas0.read();

      char jsonBuffer[512];
      serializeJson(doc,jsonBuffer,sizeof(jsonBuffer));
      BTSerial.print(joystick); 
    }
    else{
      infrarojo1.read();
    infrarojo1.read();
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
    Serial.println(motorLeftSpeed);
    Serial.println(motorRightSpeed);
    
    delay(500);

    }
    

    //Envio de datos
    //Sensores, cambiar por datos necesarios
    //String carritoData = "S:" + String(sensor1) + "," + String(sensor2) + "," + String(sensor3) + ",";
    //Ubicacion del carrito
    //carritoData += "P:" + String(x) + "," + String(y) + "\n";
    //HM10.print(carritoData);
  
}

float calcularDistancia(float x, float y, float xBaliza, float yBaliza) {
  // Cálculo de la distancia mediante el teorema de Pitágoras
  return sqrt(pow(x - xBaliza, 2) + pow(y - yBaliza, 2));
}

float trilateracionX(float d1, float d2, float d3, float x1, float x2, float x3) {
  // Cálculo de la coordenada X mediante trilateración
  float A = 2 * x2 - 2 * x1;
  float B = 2 * x3 - 2 * x2;
  float C = pow(d1, 2) - pow(d2, 2) - pow(x1, 2) + pow(x2, 2) - pow(x2, 2) + pow(x3, 2);
  float D = pow(d2, 2) - pow(d3, 2) - pow(x2, 2) + pow(x3, 2) - pow(x3, 2) + pow(x2, 2);
  float x = (C * (2 * x3 - 2 * x2) - D * (2 * x2 - 2 * x1)) / (4 * (x3 - x2));
return x;
}

float trilateracionY(float d1, float d2, float d3, float y1, float y2, float y3) {
  // Cálculo de la coordenada Y mediante trilateración
  float A = 2 * y2 - 2 * y1;
  float B = 2 * y3 - 2 * y2;
  float C = pow(d1, 2) - pow(d2, 2) - pow(y1, 2) + pow(y2, 2) - pow(y2, 2) + pow(y3, 2);
  float D = pow(d2, 2) - pow(d3, 2) - pow(y2, 2) + pow(y3, 2) - pow(y3, 2) + pow(y2, 2);
  float y = (C * (2 * y3 - 2 * y2) - D * (2 * y2 - 2 * y1)) / (4 * (y3 - y2));
return y;
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