#include "Sonido.h"

Sonido::Sonido(int _pin, int _numero)
{
  pinMode(_pin, INPUT_PULLUP);
  pin = _pin;
  numero = _numero;
}

int Sonido::read()
{
  bool  valor =  digitalRead(pin) ; //leemos el estado del sensor
  if ( valor == true ) //Si está activada la salida D0
  {
    int respuesta = 1;
    return respuesta;
    delay (1000);
  }
  else
  {
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