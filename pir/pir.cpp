#include "pir.h"
Pir::Pir(int _pin, int _numero)
{
  pinMode(_pin, INPUT);
  pin = _pin;
  numero = _numero;
}

int Pir::read()
{
  valor = digitalRead(pin);
  return valor;
}

void Pir::show()
{
  Serial.print("M");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(valor);
}

