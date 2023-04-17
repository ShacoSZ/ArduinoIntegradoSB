#include <SoftwareSerial.h>

// Configuración de los módulos HM-10
SoftwareSerial hm10Serial(10, 11); // RX, TX
const int numBalizas = 3; // número de balizas en el sistema
const int baliza1 = 1; // identificador de la primera baliza
const int baliza2 = 2; // identificador de la segunda baliza
const int baliza3 = 3; // identificador de la tercera baliza
const float distEntreBalizas = 4.0; // distancia en metros entre balizas
const float distBaliza1 = 0.0; // distancia en metros de la baliza 1 al origen (el Rover)
const float distBaliza2 = 4.0; // distancia en metros de la baliza 2 al origen (el Rover)
const float distBaliza3 = 8.0; // distancia en metros de la baliza 3 al origen (el Rover)

void setup() {
  Serial.begin(9600);
  hm10Serial.begin(9600);
}

void loop() {
  // Leer datos de cada baliza
  float dist1 = readDistance(baliza1);
  float dist2 = readDistance(baliza2);
  float dist3 = readDistance(baliza3);
  
  // Calcular posición del Rover
  float x = (pow(dist1, 2) - pow(dist2, 2) + pow(distEntreBalizas, 2)) / (2 * distEntreBalizas);
  float y = sqrt(pow(dist1, 2) - pow(x, 2));
  
  // Ajustar la posición según la posición de la baliza 1
  x += distBaliza1;
  y += 0; // la baliza 1 es el origen en el eje y
  
  // Imprimir la posición del Rover
  Serial.print("Posición del Rover: (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println(")");
  
  delay(1000); // espera para volver a leer los datos de las balizas
}

// Leer la distancia de una baliza
float readDistance(int idBaliza) {
  // Enviar comando para leer distancia
  String command = "AT+DIS?"; // comando para leer distancia
  command += String(idBaliza); // añadir identificador de la baliza
  command += "\r\n";
  hm10Serial.print(command);
  
  // Leer respuesta de la baliza
  String response = "";
  while (response.indexOf("+DIS") < 0) {
    if (hm10Serial.available()) {
      response += (char)hm10Serial.read();
    }
  }
  
  // Obtener la distancia de la respuesta
  int index = response.indexOf(":");
  String distStr = response.substring(index + 1, response.length() - 1);
  float dist = distStr.toFloat();
  
  return dist;
}
