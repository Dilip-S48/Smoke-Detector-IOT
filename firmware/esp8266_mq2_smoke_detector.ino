#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASS     "YOUR_WIFI_PASSWORD"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "YOUR_AIO_USERNAME"
#define AIO_KEY         "YOUR_AIO_KEY"

const int MQ2_PIN = A0;
const int BUZZER_PIN = D5;
const int LED_PIN = D6;
int SMOKE_THRESHOLD = 700;
const unsigned long PUBLISH_INTERVAL_MS = 15000UL;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish feed_smoke_raw   = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/smoke_raw");
Adafruit_MQTT_Publish feed_alarm       = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/alarm");
Adafruit_MQTT_Publish feed_airquality  = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/air_quality_pct");

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
}

void connectMQTT() {
  while (mqtt.connect() != 0) {
    mqtt.disconnect();
    delay(5000);
  }
}

int readAveragedADC(uint8_t samples = 10) {
  long sum = 0;
  for (uint8_t i = 0; i < samples; i++) { sum += analogRead(MQ2_PIN); delay(5); }
  return (int)(sum / samples);
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  connectWiFi();
  connectMQTT();
}

unsigned long lastPublish = 0;
void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.processPackets(10);
  if (!mqtt.ping()) mqtt.disconnect();

  int raw = readAveragedADC(12);
  int pct = map(raw, 0, 1023, 0, 100);
  bool alarm = raw >= SMOKE_THRESHOLD;

  digitalWrite(LED_PIN, alarm ? HIGH : LOW);
  if (alarm) tone(BUZZER_PIN, 2000, 200); else noTone(BUZZER_PIN);

  unsigned long now = millis();
  if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
    lastPublish = now;
    feed_smoke_raw.publish(raw);
    feed_airquality.publish(pct);
    feed_alarm.publish(alarm ? 1 : 0);
  }
}
