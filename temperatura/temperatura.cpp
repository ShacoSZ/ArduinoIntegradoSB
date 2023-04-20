#include "temperatura.h"
#include <DHT11.h>

Temperatura::Temperatura(int _pin,int numero){
  pin =_pin;
  numero = _numero;
  DHT11 temp(pin);
}

int Temperatura::readTEMP(){
    int err;
    float tempura, hum;
       if((err = temp.read(hum, tempura)) == 0)    // Si devuelve 0 es que ha leido bien
          {
            temperatura = tempura;
            humedad = hum;
            return temperatura;
          }
       delay(1000); 
}

int Temperatura::readHUM(){
    int err;
    float tempura, hum;
       if((err = temp.read(hum, tempura)) == 0)    // Si devuelve 0 es que ha leido bien
          {
            temperatura = tempura;
            humedad = hum;
            return humedad;
          }
       delay(1000); 
}

void Temperatura::show(){
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println();
}