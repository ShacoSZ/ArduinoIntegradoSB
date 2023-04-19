#include <SoftwareSerial.h>
#include "SensorInfrarojo.h"
#include "Sonido.h"
#include "voltaje.h"
#include "vexMotor.h"
#include "Distancia.h"
#include "pir.h"
#include "voltajesensor.h"

/************** Ultrasonico **************/
  Distancia us1 = Distancia(5, 6, 0);

  const int numeroUS = 1; 
  Distancia sensores_sonicos[] = {us1};
  float val_sensores_sonicos[numeroUS];
  
/************* Sensor Sonido **************/
  Sonido sound1 = Sonido(9,0);

  const int numero_sound = 1;
  Sonido sensores_sonido[] = {sound1};
  float val_sensores_sonido[numero_sound];

/************* Sensor Infrarojo **************/
  SensorInfrarojo infrarojo1 = SensorInfrarojo(10,0);

  const int numero_infrarojo = 1;
  SensorInfrarojo sensores_infrarojo[] = {infrarojo1};
  float val_sensores_infrarojo[numero_infrarojo];

/************* Sensor PIR *************/
  Pir mov1 = Pir(2, 0);

  const int numeroMov = 1;
  Pir sensores_mov[] = {mov1};
  float val_sensores_mov[numeroMov];

/************ Voltaje_Sensor ****************/  
  voltajesensor volt1 = voltajesensor(11,0)

  const int numero_volt = 1;
  voltajesensor sensores_volt[] = {volt1};
  float val_sensor_volt[numero_volt];

SoftwareSerial HM10(2, 3); // RX, TX
int carritoX, carritoY;

void setup() {
  Serial.begin(9600);
  HM10.begin(9600);
}

void loop() {
  int i = 0;
  // Leer datos del módulo Maestro
  if (HM10.available()) {
    String maestroData = HM10.readString();
    Serial.print("Datos del Maestro recibidos: ");
    Serial.println(maestroData);

    // Extraer las coordenadas del Maestro (X,Y)
    int delimiterIndex = maestroData.indexOf(",");
    carritoX = maestroData.substring(2, delimiterIndex).toInt();
    carritoY = maestroData.substring(delimiterIndex + 1, maestroData.length() - 2).toInt();

    // Realizar triangulación con las balizas
    float distancia1 = calcularDistancia(carritoX, carritoY, baliza1X, baliza1Y);
    float distancia2 = calcularDistancia(carritoX, carritoY, baliza2X, baliza2Y);
    float distancia3 = calcularDistancia(carritoX, carritoY, baliza3X, baliza3Y);
    float x = trilateracionX(distancia1, distancia2, distancia3, baliza1X, baliza2X, baliza3X);
    float y = trilateracionY(distancia1, distancia2, distancia3, baliza1Y, baliza2Y, baliza3Y);


    //Logica de sensores
 
    val_sensor_volt+= "volt: " + String(sensores_volt[i].read(););
    val_sensores_sonido += "Sonido: " + String(sensores_sonido[i].read(););
    val_sensores_mov += "PIR: " + String(sensores_mov[i].read(););
    val_sensores_sonicos += "Distancia Ultrasonico: " + String(sensores_sonicos[i].read(););
    val_sensores_infrarojo += "Infrarojo: " + String(sensores_infrarojo[i].read(););
    
    //Envio de datos
    //Sensores, cambiar por datos necesarios
    String carritoData = "S:" + String(sensor1) + "," + String(sensor2) + "," + String(sensor3) + ",";
    //Ubicacion del carrito
    carritoData += "P:" + String(x) + "," + String(y) + "\n";
    HM10.print(carritoData);
    i+=1;
  }
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