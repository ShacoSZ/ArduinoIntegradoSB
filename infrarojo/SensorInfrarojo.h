#ifndef SENSORINFRAROJO_H
#define SENSORINFRAROJO_H

#include <Arduino.h>

class SensorInfrarojo
{
  public:
    SensorInfrarojo(int _pin, int _numero);
    int read();
    void show();
  private:
    int pin;
    bool valor;
    int respuesta;
};
#endif