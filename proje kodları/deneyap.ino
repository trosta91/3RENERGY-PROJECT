#include <ThingSpeakWriter_asukiaaa.h>

#define WRITE_API_KEY "0AFCL25CB6V0TRRV"
#define WIFI_SSID "Redmi 9C"
#define WIFI_PASS "ereneren1"


ThingSpeakWriter_asukiaaa channelWriter(WRITE_API_KEY);

void connectWifiIfNotConnected(unsigned long timeoutMs = 10000) {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  uint8_t startAt = millis();
  Serial.println("Connecting to WiFi.." + String(WiFi.status()));
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    if (millis() - startAt > timeoutMs) {
      Serial.println("Cannot connect to WiFi");
      break;
    }
    delay(1000);
  }
}

 void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensor = A0;
  int sensordegeri = analogRead(sensor);
  Serial.println(sensordegeri)
  connectWifiIfNotConnected();
  channelWriter.setField(1, String(sensordegeri));
  int result = channelWriter.writeFields();
  if (result < 0) {
    Serial.println("Failed to send data");
  } else if (result != 200) {
    Serial.println("Sent data but failed at status code: " + String(result));
  } else {
    Serial.println("Succeeded in sending data.");
  }
  delay(10000);
}
