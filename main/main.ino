#include <SoftwareSerial.h>

SoftwareSerial HM10(2, 3); // RX, TX
int sensor1, sensor2, sensor3, carritoX, carritoY;

void setup() {
  Serial.begin(9600);
  HM10.begin(9600);
}

void loop() {
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


    //Envio de datos
    //Sensores, cambiar por datos necesarios
    String carritoData = "S:" + String(sensor1) + "," + String(sensor2) + "," + String(sensor3) + ",";
    //Ubicacion del carrito
    carritoData += "P:" + String(x) + "," + String(y) + "\n";
    HM10.print(carritoData);
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