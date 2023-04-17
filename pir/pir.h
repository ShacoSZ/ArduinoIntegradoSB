#ifndef PIR_H
#define PIR_H
#include <Arduino.h>

class Pir
{
  public:
    Pir(int _pin, int _numero);
    int read();
    void show();
  private:
    int pin;
    int numero;
    int valor;
};

#endif