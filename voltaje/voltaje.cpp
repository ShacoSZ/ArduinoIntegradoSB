#include "voltaje.h"

Voltaje::Voltaje(int pin){
    _pin = pin;
}

void Voltaje::setup(){
    pinMode(_pin, INPUT);
}

float Voltaje::read(){
    return (map(volt,0,1023, 0, 2500) + 20)/100;
}