#include "Sonido.h"

Sonido::Sonido(int _pin, int _numero)
{
  pin = _pin;
  numero = _numero;
}

int Sonido::read()
{
  respuesta = analogRead(pin) ;
  return respuesta;
  delay(1000);
}

void Sonido::show()
{
  Serial.print("S");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(respuesta);
}