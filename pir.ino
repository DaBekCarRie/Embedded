#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
const char* LINE_TOKEN = "COfu9/s2C0uKvsOkkgUmyI44TTlNPVv6W1f7lqgJGWEe7L6ziUIn4njxyKIb29N4HlxlYrcu4Yiti2Bq1QFt2rXHnzmlS0eApTj7Ql9ptJHjj+R4ut2VqrN+/aKg3Gr0VmGlXRYPwq5qzuqIRd4IrAdB04t89/1O/w1cDnyilFU=";
bool systemOn = false;
bool light = false;
void toggleLed() {
  systemOn = !systemOn;
}
void toggleLight() {
  light = !light;
}


const int BUZZER = 33;
const int PIR_PIN_1 = 13;
const int PIR_PIN_2 = 23;
const int PIR_PIN_3 = 19;
const int LED_PIN_1 = 32;
const int LED_PIN_2 = 25;
const int LED_PIN_3 = 17;


void setup() {
  Serial.begin(115200);

  WiFi.begin("Joja-iphone", "55555555");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");

  server.on("/toggle-light", HTTP_GET, [](AsyncWebServerRequest *request){
    toggleLight();
    request->send(200, "text/plain", light ? "Light on" : "Light off");
  });
  server.on("/toggle-pir", HTTP_GET, [](AsyncWebServerRequest *request){
    toggleLed();
    request->send(200, "text/plain", systemOn ? "System on" : "System off");
  });

  // Start the server
  server.begin();

  pinMode(PIR_PIN_1, INPUT);
  pinMode(PIR_PIN_2, INPUT);
  pinMode(PIR_PIN_3, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {

    int PIR_STATE_1 = digitalRead(PIR_PIN_1);
    int PIR_STATE_2 = digitalRead(PIR_PIN_2);
    int PIR_STATE_3 = digitalRead(PIR_PIN_3);
    // อยู่บ้าน
    if(!systemOn){
      digitalWrite(LED_PIN_1, LOW);
      digitalWrite(LED_PIN_2, LOW);
      digitalWrite(LED_PIN_3, LOW);
      digitalWrite(BUZZER, LOW);
      if (PIR_STATE_1 == HIGH) {
        Serial.println("Motion Detected 1");
        digitalWrite(LED_PIN_1, HIGH);
        delay(5000);
        digitalWrite(LED_PIN_1, LOW);
      }
      if (PIR_STATE_2 == HIGH) {
        Serial.println("Motion Detected 2");
        digitalWrite(LED_PIN_2, HIGH);
        delay(5000);
        digitalWrite(LED_PIN_2, LOW);
      }
      if (PIR_STATE_3 == HIGH) {
        Serial.println("Motion Detected 3");
        digitalWrite(LED_PIN_3, HIGH);
        delay(5000);
        digitalWrite(LED_PIN_3, LOW);
      }
      else {
        Serial.println("ไม่มีใครผ่านตอนอยู่บ้าน");
      }
      delay(500);
    }
    
    // not home systemOn==true
    else if(systemOn)
    {
    digitalWrite(LED_PIN_1, light ? HIGH : LOW);
    digitalWrite(LED_PIN_2, light ? HIGH : LOW);
    digitalWrite(LED_PIN_3, light ? HIGH : LOW);
    digitalWrite(BUZZER, light ? HIGH : LOW);

    if (PIR_STATE_1 == HIGH) {
      Serial.println("Motion detected 1!");
      sendLineNotify("Motion detected 1!");
      light=true;
    }
    if (PIR_STATE_2 == HIGH) {
      Serial.println("Motion detected 2!");
      sendLineNotify("Motion detected 2!");
      light=true;
    }
    if (PIR_STATE_3 == HIGH) {
      Serial.println("Motion detected 3!");
      sendLineNotify("Motion detected 3!");
      light=true;
    }
    }
    
};

void sendLineNotify(String message) {
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