#include "Gas.h"

Sens_Gas::Sens_Gas(int _pin, int _numero)
{
  pin = _pin;
  pinMode(pin, INPUT);
  numero = _numero;
}

int Sens_Gas::read()
{
  valor = digitalRead(pin);  //lectura digital de pin
 
  if (valor) 
  { 
    respuesta = 1;           
    return respuesta;
  }
  else
  {
    respuesta = 0;           
    return respuesta;    
  }
  delay(1000);
}

void Sens_Gas::show()
{
  Serial.print("G");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(respuesta);
}