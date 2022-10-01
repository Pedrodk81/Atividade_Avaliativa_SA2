#include <DHTesp.h>
#include "HTTPClient.h"
#include "WiFi.h"

const char *ssid = "Wokwi-GUEST";
const char *password = "";
const String url = "https://api.thingspeak.com/update?api_key=VP9PDXUL6XF0WAQC&";

const int activePin1 = 2;
const int activePin2 = 4;

HTTPClient http;
DHTesp dhtSensor;

void setup()
{
    Serial.begin(115200);
    dhtSensor.setup(13, DHTesp::DHT22);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(WiFi.status());
        Serial.println("Finalizando Setup");
    }
    pinMode(activePin1, OUTPUT);
    pinMode(activePin2, OUTPUT);
    Serial.println("Finalizado Setup !");
}

void loop()
{
    // capturando temperatura e Humidade
    float temperatura = dhtSensor.getTemperature();
    float humidade = dhtSensor.getHumidity();

    String path = url + "field1=" + String(temperatura) + "&field2=" + String(humidade);

    http.begin(path);

    int httpCode = http.GET();
    String payload = http.getString();

    Serial.println("HttpCode:" + String(httpCode));
    Serial.println("Paylaod:" + payload);

    delay(3000);

    // imprimundo dados capturados
    Serial.println("Temperatura :" + String(temperatura) + "C");
    Serial.println("Humidade :" + String(humidade) + "%");

    digitalWrite(activePin1, HIGH);
    digitalWrite(activePin2, HIGH);
    delay(600);

    digitalWrite(activePin1, LOW);
    digitalWrite(activePin2, LOW);
    delay(600);
}
