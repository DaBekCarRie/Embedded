#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

const char* ssid = "Joja-iphone";
const char* password = "55555555";
const char* LINE_TOKEN = "COfu9/s2C0uKvsOkkgUmyI44TTlNPVv6W1f7lqgJGWEe7L6ziUIn4njxyKIb29N4HlxlYrcu4Yiti2Bq1QFt2rXHnzmlS0eApTj7Ql9ptJHjj+R4ut2VqrN+/aKg3Gr0VmGlXRYPwq5qzuqIRd4IrAdB04t89/1O/w1cDnyilFU=";
#define LIGHT_SENSOR_PIN 36
#define BUZZER 14
bool systemOn = false;
void toggleLed() {
  systemOn = !systemOn;

}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected.");
  // set OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed.");
    while (1);
  }
  display.clearDisplay();
  display.display();
  // server
  server.on("/toggle-ldr", HTTP_GET, [](AsyncWebServerRequest *request){
    toggleLed();
    request->send(200, "text/plain", systemOn ? "System on" : "System off");
  });

  // Start the server
  server.begin();
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  if(systemOn){
   int analogValue = analogRead(LIGHT_SENSOR_PIN);
  if (analogValue < 3000) {
    sendLineMessage("Sensor blocked!");
    digitalWrite(BUZZER,HIGH);
    display.clearDisplay();
    display.setTextSize(6);
    display.setTextColor(WHITE);
    display.setCursor(15,5);
    display.println("SOS");
    display.display();
    delay(1000);
    digitalWrite(BUZZER,LOW);

  }
  else{
    display.clearDisplay();
    display.display();
  }

  delay(500);
 }
  else{
    Serial.println("false");
    display.clearDisplay();
    display.display();
  }
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