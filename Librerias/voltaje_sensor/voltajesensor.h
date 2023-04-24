#ifndef VOLTAJESENSOR_H
#define VOLTAJESENSOR_H

#include <Arduino.h>

class voltajesensor
{
  public:
    voltajesensor(int _pin, int _numero);
    int read();
    void show();
  private:
    int pin;
    int numero;
    int valor;
};
#endif