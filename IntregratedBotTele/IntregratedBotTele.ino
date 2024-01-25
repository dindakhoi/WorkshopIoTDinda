#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;
const char* ssid ="Hello there";
const char* password ="gitagita";
#define CHAT_ID "6326756976"
#define BOTtoken "6731581597:AAG-m0iFaUeFDH8cR53_qFRfjteTbYd7rOo"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  Serial.begin(115200);
  Serial.print("Conneting Wifi:");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  } 

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Tunggu sebentar...Monitoring akan dimulai","");

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
  bot.sendMessage(CHAT_ID, "Monitoring tanaman SMKN 7 Baleendah");
  kirimPesanTelegram(h, t, M);
}
void kirimPesanTelegram(float h, float t, int M) {
  String pesan = "Suhu saat ini: " + String(t, 2) + "°C\n" +
                 "Humiditas udara saat ini: " + String(h, 2) + "%\n" +
                 "Tingkat kelembaban tanah saat ini: " + String(M) + "%\n";

  if (bot.sendMessage(CHAT_ID, pesan, "Markdown")) {
    Serial.println("Pesan berhasil dikirim");
  } else {
    Serial.println("Gagal mengirim pesan");
  }

  delay(1000);  // Menunggu sejenak sebelum mengirim pesan lagi
}