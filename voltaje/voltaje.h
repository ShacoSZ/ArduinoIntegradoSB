#ifndef VOLTAJE_H
#define VOLTAJE_H
#include <Arduino.h>

class Voltaje{
    public:
        Voltaje(int pin);
        void setup();
        float read();
    private:
        int _pin;
};

#endif
