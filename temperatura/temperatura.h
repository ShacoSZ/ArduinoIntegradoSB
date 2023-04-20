#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <Arduino.h>

class Temperatura
{
public:
Distancia(int _pin,int numero);
void setup();
int readTEMP();
int readHUM();
void show();

private:
int pin;
int numero;
float temperatura;
float humedad;
};

#endif