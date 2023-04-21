#include "voltajesensor.h"

voltajesensor::voltajesensor(int _pin, int _numero)
{
  pin = _pin;
  #define ANALOG_IN_PIN pin
  numero = _numero;
}

int voltajesensor::read()
{
    float adc_voltage = 0.0;
    float in_voltage = 0.0;
    
    float R1 = 30000.0;
    float R2 = 7500.0; 
    
    float ref_voltage = 5.0;
    
    int adc_value = 0;

    adc_value = analogRead(ANALOG_IN_PIN);
   
    adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
    
    in_voltage = adc_voltage / (R2/(R1+R2)); 
    
    valor = in_voltage;
    return valor;
    
    delay(500);

}

void voltajesensor::show()
{
  Serial.print("VS");
  Serial.print(numero);
  Serial.print(":");
  Serial.println(valor);
}