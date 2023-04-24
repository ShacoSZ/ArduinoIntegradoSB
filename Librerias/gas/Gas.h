#ifndef GAS_H
#define GAS_H

#include <Arduino.h>

class Sens_Gas
{
public:
Sens_Gas(int _pin,int numero);
void setup();
int read();
void show();

private:
int pin;
int numero;
bool valor;
int respuesta;
};
#endif
