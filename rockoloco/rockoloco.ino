#include <SoftwareSerial.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;
JsonArray palabras = doc.to<JsonArray>();

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

    JsonObject Sensao = palabras.createNestedObject();

    Sensao["Clave: "] = clave;
    Sensao["Tipo: "] = tipo;
    Sensao["Valores: "] = valores;
    Sensao["Dato: "] = dato;
    Sensao["Pines: "] = pines;

    char jsonBuffer[512];
    serializeJson(doc,jsonBuffer,sizeof(jsonBuffer));

    Serial.println(jsonBuffer);
    delay(1000);
}