#include <SoftwareSerial.h>

int i=0;
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    int echoPin=8;
    int triggerPin=9;

    String clave = "ULT01";
    String tipo = "Ultrasonico"; 
    String valores = String(48.10);
    String dato = "CM"; 
    String pines = String(echoPin) + " y " + String(triggerPin);

    String dict = "";

     dict = "Clave: " + String(clave) + ", " + "Tipo: " + String(tipo) + ", " 
    + "valores: " + String(valores) + ", "+ "Dato: " + String(dato) + ", " + "Pines: " + String(pines);

    Serial.println(dict);
    delay(5000);
}