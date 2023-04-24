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

SoftwareSerial BTSerial(11, 10); // RX, TX
int carritoX, carritoY;
int count = 0;
vexMotor motorLeft(38); // pinPWM del motor izquierdo
vexMotor motorRight(39); // pinPWM del motor derecho
String data; // variable para almacenar los datos recibidos
int x  = 509, y = 504; // variables para almacenar los valores x e y
int aux;
int prevX = 0;
int prevY = 0;
void setup() {
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
    x = data.substring(0, commaPos).toInt();
    // obtiene la subcadena después de la coma y la convierte a un entero
    y = data.substring(commaPos + 1).toInt();
    // imprime los valores de x e y en la consola serial
    Serial.print("x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);
    motores(x, y);
    aux = 0;  
  }
  }
    aux+=1;
    delay(500);
    if (aux==4){
      aux = 0;
      if ((x > 505 && x < 513)&&(y > 501 && y < 509)) {
      sensores();
      }
    }
    
}

String JsonSensor(String clave, float valores) {
  DynamicJsonDocument doc(1024);
  doc["clave"] = clave;
  doc["valores"]   = valores;
  String output;
  serializeJson(doc, output);
  return output;
}

void motores(int x, int y){
  int joyXx = x;
  int joyYx = y;

  // mapear la entrada del joystick a la velocidad del motor
  int motorLeftSpeed = map(joyYx, 0, 1025, 33, 115)+23;
  int motorRightSpeed = map(joyYx,  0, 1025, 33, 115)-9;
  int turningSpeed = map(joyXx, 0, 1023, -40, 40);
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

float antSon = 0, antBat1, antBat2, antUlt1, antUlt2, antHum, antTem, antGas, antIfr1,antIfr2, antPir1,antPir2;

void sensores(){
  //Logica de sensores
  float ult1 = us1.read();
  if (ult1 > 0){
    Serial.println(JsonSensor("Ult0",ult1));
  }

  float ult2 = us2.read();
  if (ult2 > 0){
    Serial.println(JsonSensor("Ult1",ult2));
  }
  float Son = sound1.read();
  if (Son != antSon){
    Serial.println(JsonSensor("Son0",Son));
    antSon = Son;
  }

  float Tem = Temperatura(9,0);
  if (Tem != antTem){
    Serial.println(JsonSensor("Tem0",Tem));
    antTem=Tem
  }


  Serial.println(JsonSensor("Hum0",Humedad(9,0)));
  
  Serial.println(JsonSensor("Bat0",volt1.read()));
  Serial.println(JsonSensor("Bat1",volt2.read()));
  Serial.println(JsonSensor("Pir0",mov1.read()));
  Serial.println(JsonSensor("Pir1",mov2.read()));
  Serial.println(JsonSensor("Ifr0",infrarojo1.read()));
  Serial.println(JsonSensor("Ifr1",infrarojo2.read()));
  Serial.println(JsonSensor("Gas0", gas0.read()));

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