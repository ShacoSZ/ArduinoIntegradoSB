#include "voltaje.h"
#include "vexMotor.h"
#include "ultrasonico.h"
#include "pir.h"

Voltaje bat1(0);
Voltaje bat2(1);

void setup(){
  bat1.setup();
  bat2.setup();
    Serial.begin(9600);
}

void loop(){
    Serial.println(bat1.read());
    Serial.println(bat2.read());
    delay(1000);
}