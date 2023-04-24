#include "Distancia.h"

Distancia::Distancia(int _echoPin,int _triggerPin,int _numero){
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  triggerPin = _triggerPin;
  echoPin= _echoPin;
  numero = _numero;
}

int Distancia::read(){
  long duration, distanceCm;
  digitalWrite(triggerPin,LOW); //Para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(triggerPin, HIGH); //Generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292/ 2; //Convertimos a distancia, en cm
  distance = distanceCm;
  return distanceCm;
}

void Distancia::show(){
  Serial.print("ult");
  Serial.print(numero);
  Serial.print("  :");
  Serial.print(distance);
  Serial.println();
}