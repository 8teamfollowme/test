#include "DHT.h"

#define DHTPIN 27
#define DHTTYPE DHT11
// TIP120 IC가 연결된 핀 설정
const int TIP_PIN = 10;

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // TIP120 IC 핀을 출력으로 설정
  pinMode(TIP_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if (h < 40 || t > 20 || t < 15) {
    digitalWrite(TIP_PIN, HIGH);
  }

}
