#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <Arduino.h>
#include <DHT.h>  // Incluimos la librería DHT.h

class Temperatura
{
public:
    Temperatura(int _pin, int _numero);
    void setup();
    int readTEMP();
    int readHUM();
    void show();

private:
    int pin;
    int numero;
    float temperatura;
    float humedad;
    DHT temp;  // Declaramos la variable temp como miembro de la clase Temperatura
};

#endif
