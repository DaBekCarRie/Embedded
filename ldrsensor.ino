#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Joja-iphone";
const char* password = "55555555";
const char* LINE_TOKEN = "vQjgfWU1tNIbppUb+ehE78ddXZ+jdgYW4ZDNPmPIGIfvdsRyvbCLpQz25mz3bSh9/zEDT660xMW498uVAB0aBxQzJ+VrbykZSDYnag9Hp6OmtI3Om8eSxS8T1LIxGZIsv7aJR3crO9xKqH/m2QLW7gdB04t89/1O/w1cDnyilFU=";
#define LIGHT_SENSOR_PIN 36
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected.");
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  if (analogValue < 3000) {
    sendLineMessage("Sensor blocked!");
  }

  delay(500);
}


void sendLineMessage(String message) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/push");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(LINE_TOKEN));
  String requestBody = "{\"to\":\"Ucafd9cf95567fb85c70979e6d7987ce3\",\"messages\":[{\"type\":\"text\",\"text\":\"" + message + "\"}]}";
  int httpResponseCode = http.POST(requestBody);
  if (httpResponseCode > 0) {
    Serial.println("Line message sent successfully!");
  } else {
    Serial.println("Error sending Line message.");
  }
  http.end();
}
