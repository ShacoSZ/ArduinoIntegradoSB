#include "SensorInfrarojo.h"

Sonido::Sonido(int _pin, int _numero)
{
  pinMode(_pin, INPUT_PULLUP);
  pin = _pin;
  numero = _numero;
}

int Sonido::read()
{
  bool  valor =  digitalRead(sensor) ; //leemos el estado del sensor
  if ( valor == true ) //Si está activada la salida D0
  {
    Serial.println("Hay ruido");
    int respuesta = 1;
    return respuesta;
    delay (1000);
  }
  else
  {
    Serial.println("No hay ruido");
    int respuesta = 0;
    return respuesta;
    delay(1000);
  }
}

void Sonido::show()
{
  Serial.print("S");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(respuesta);
}