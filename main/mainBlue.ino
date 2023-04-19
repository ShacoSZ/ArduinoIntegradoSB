#include <SoftwareSerial.h>
#include "SensorInfrarojo.h"
#include "Sonido.h"
#include "voltaje.h"
#include "vexMotor.h"
#include "ultrasonico.h"
#include "pir.h"
#include "voltajesensor.h"


SoftwareSerial HM10(2, 3); // RX, TX
int x, y;
bool izq, der;

ultrasonico ultIzquierdo(4, 5);
ultrasonico ultDerecho(6, 7);


void setup() {
    Serial.begin(9600);
    HM10.begin(9600);
    ultIzquierdo.setup();
    ultDerecho.setup();
}

void loop() {
  // Leer datos del módulo Maestro
  if (HM10.available()) {
    String maestroData = HM10.readString();
    Serial.print("Datos del Maestro recibidos: ");
    Serial.println(maestroData);

    // Extraer las coordenadas del Maestro (X,Y)
    int delimiterIndex = maestroData.indexOf(",");
    x = maestroData.substring(2, delimiterIndex).toInt();
    y = maestroData.substring(delimiterIndex + 1, maestroData.length() - 2).toInt();
    motores(x, y, izq, der);
    //Logica de sensores


    //Envio de datos
    //Sensores, cambiar por datos necesarios
    String carritoData = "{ultIzq:" + String(sensor1) + "}," + "{ultDer:" + String(sensor1) + "}," +;
    //Ubicacion del carrito
    HM10.print(carritoData);
  }, 
}

void motores(int x, int y, bool ultIzq, bool ultDer){
    if ultIzq == false && ultDer == true{
        motorLeft.setSpeed(33);
    }
    if ultIzq == true && ultDer == false{
        motorRight.setSpeed(33);
    }
    if ultIzq == false && ultDer == false{
        motorLeft.setSpeed(33);
        motorRight.setSpeed(33);
    }
    if ultIzq == true && ultDer == true{
        int motorLeftSpeed = map(y, -5, 755, 33, 115)+23;
        int motorRightSpeed = map(y, -5, 755, 33, 115)-9;
        int turningSpeed = map(x, 0, 1023, -40, 40);

        motorLeftSpeed += turningSpeed;
        motorRightSpeed -= turningSpeed;

        if (motorLeftSpeed >= 100){
        motorLeftSpeed = 99;
        }
        if (motorRightSpeed >= 100){
        motorRightSpeed = 99;
        }
        if (motorLeftSpeed < 33){
        motorLeftSpeed = 33;
        }
        if (motorRightSpeed < 33){
        motorRightSpeed = 33;
        }

        motorLeft.setSpeed(motorLeftSpeed);
        motorRight.setSpeed(motorRightSpeed);
    }
    
}
