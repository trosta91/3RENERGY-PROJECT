#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>

const char* ssid = "REDMİ 9C";
const char* password = "ereneren1";
const char* webSocketServerAddress = "ws://[sunucu_ip_adresi]:8080"; 

WebServer server(80);
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("WiFi'ye bağlanılıyor...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi'ye bağlanıldı.");

  
  server.on("/", HTTP_GET, handleRoot);
  server.begin();

 
  webSocket.begin(webSocketServerAddress);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop(); 
  
 
  int sensorValue = analogRead(A0); 
  String message = "{\"value\": " + String(sensorValue) + "}";
  webSocket.sendTXT(message);
  delay(1000); 
}

void handleRoot() {
 
  server.send(200, "text/html", index_html);
}
