#include "voltaje.h"
#include "vexMotor.h"
#include "ultrasonico.h"
#include "pir.h"
#include "SensorInfrarojo.h"
#include "Sonido.h"


//declarar sensores


//declarar motores
vexMotor izq(2);
vexMotor der(3);

void setup(){
  izq.setup();
  der.setup();
  Serial.begin(9600);
}

void loop(){
    Serial.println(bat1.read());
    Serial.println(bat2.read());
    delay(1000);
}