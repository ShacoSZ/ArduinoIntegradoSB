#ifndef SONIDO_H
#define SONIDO_H

#include <Arduino.h>

class Sonido
{
  public:
    Sonido(int _pin, int _numero);
    int read();
    void show();
  private:
    int pin;
    bool valor;
    int respuesta;
};
#endif
