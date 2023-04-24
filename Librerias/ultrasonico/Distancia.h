#ifndef DISTANCIA_H
#define DISTANCIA_H

#include <Arduino.h>

class Distancia
{
public:
Distancia(int _echoPin, int _triggerPin, int numero);
void setup();
int read();
void show();

private:
int echoPin;
int triggerPin;
int numero;
int distance;
};

#endif