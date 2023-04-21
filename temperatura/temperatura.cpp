#include "temperatura.h"
#include <DHT.h>

Temperatura::Temperatura(int _pin, int _numero) {
  pin = _pin;
  numero = _numero;
  temp = DHT(pin, DHT11);
  temp.begin();
}

int Temperatura::readTEMP() {
  temperatura = temp.readTemperature();
  delay(1000);
  return temperatura;
}

int Temperatura::readHUM() {
  humedad = temp.readHumidity();
  delay(1000);
  return humedad;
}

void Temperatura::show() {
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" Humedad: ");
  Serial.print(humedad);
  Serial.println();
}

