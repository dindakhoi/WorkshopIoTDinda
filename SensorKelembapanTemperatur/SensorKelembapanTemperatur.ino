#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

void setup() {
  delay(2000);
  Serial.print("Workshop Monitoring Tanaman SMKn 7 Baleendah\n");
  dht.begin();
}

void loop() {
  sensor_analog = analogRead(sensor_pin);
  M =(100-((sensor_analog/4095.00)* 100));
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(h) || isnan(t) || isnan(M)) {
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
  Serial.print("Kelembapan air tanah: ");
  Serial.print(M);
  Serial.println(" %");
  delay(2000);
}