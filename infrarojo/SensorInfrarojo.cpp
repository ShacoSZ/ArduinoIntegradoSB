#include "SensorInfrarojo.h"

SensorInfrarojo::SensorInfrarojo(int _pin, int _numero)
{
  pinMode(_pin, INPUT);
  pin = _pin;
  numero = _numero;
}

int SensorInfrarojo::read()
{
  int value = 0;
  value = digitalRead(pin);  //lectura digital de pin
 
  if (value == HIGH) 
  { 
    int respuesta = 1;           
    return respuesta;
  }
  else
  {
    int respuesta = 0;           
    return respuesta;    
  }
  delay(1000);
}

void SensorInfrarojo::show()
{
  Serial.print("S_I");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(respuesta);
}