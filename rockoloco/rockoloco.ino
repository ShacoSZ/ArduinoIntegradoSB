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

    Sensao["clave"] = clave;
    Sensao["tipo"] = tipo;
    Sensao["valores"] = valores;
    Sensao["dato"] = dato;
    Sensao["pines"] = pines;

    char jsonBuffer[512];
    serializeJson(doc,jsonBuffer,sizeof(jsonBuffer));

    Serial.println(jsonBuffer);
    delay(1000);
}