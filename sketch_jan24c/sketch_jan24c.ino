#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop Monitoring Tanaman SMKn 7 Baleendah\n");
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(h) || isnan(t)) {
    Serial.println("Sensor Tidak Terbaca!");
    return;
  }
  Serial.print("==========Monitoring Tanaman==========\n");
  Serial.print("Humiditas Gas Udara: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperature Lingkungan: ");
  Serial.print(t);
  Serial.println(" °C");
  delay(2000);
}