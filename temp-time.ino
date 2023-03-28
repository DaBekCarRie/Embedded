#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char* LINE_TOKEN = "COfu9/s2C0uKvsOkkgUmyI44TTlNPVv6W1f7lqgJGWEe7L6ziUIn4njxyKIb29N4HlxlYrcu4Yiti2Bq1QFt2rXHnzmlS0eApTj7Ql9ptJHjj+R4ut2VqrN+/aKg3Gr0VmGlXRYPwq5qzuqIRd4IrAdB04t89/1O/w1cDnyilFU=";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org",25200);

const int THERMISTOR1_PIN = 36; 
const int THERMISTOR2_PIN = 39;  
const int THERMISTOR3_PIN = 34;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  WiFi.begin("Joja-iphone", "55555555");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed.");
    while (1);
  }
   timeClient.begin();

  display.clearDisplay();
  display.display();

}

void loop() {
  timeClient.update();
  String currentTimeStr = timeClient.getFormattedTime();
  float R25 = 10000.0; // Thermistor resistance at 25°C
  float rawADC1 = analogRead(THERMISTOR1_PIN);
  float rawADC2 = analogRead(THERMISTOR2_PIN);
  float rawADC3 = analogRead(THERMISTOR3_PIN);
  float B25 = 4050;
  float T25 = 273+25;  
  float VPa1 = (rawADC1*3.3)/4096;
  float VPa2 = (rawADC2*3.3)/4096;
  float VPa3 = (rawADC3*3.3)/4096;
  float R1 = ((3.3/VPa1)*10000)-10000;
  float R2 = ((3.3/VPa2)*10000)-10000;
  float R3 = ((3.3/VPa3)*10000)-10000;
  float T1 = (B25/(log(R1/0.0125))) - 273;
  float T2 = (B25/(log(R2/0.0125))) - 273;
  float T3 = (B25/(log(R3/0.0125))) - 273;
  char buffer[10];
  
  if (T1 > 28) {
    sendLineNotify("Temperature 1: " + String((dtostrf(T1, 6, 2, buffer))) + " °C");
  }
  if (T2 > 28) {
    sendLineNotify("Temperature 2: " + String((dtostrf(T2, 6, 2, buffer))) + " °C");
  }
  if (T3 > 28) {    
    sendLineNotify("Temperature 3: " + String((dtostrf(T3, 6, 2, buffer))) + " °C");
  }
  
  Serial.print("Temperature 1: ");
  Serial.print(T1);
  Serial.println(" °C");

  Serial.print("Temperature 2: ");
  Serial.print(T2);
  Serial.println(" °C");

  Serial.print("Temperature 3: ");
  Serial.print(T3);
  Serial.println(" °C");

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(22,0);
  display.println(currentTimeStr);
  display.setTextSize(1);
  display.setCursor(18,30);
  display.println("Room 1 :" + String(T1));
  display.setCursor(18,40);
  display.println("Room 2 :" + String(T2));
  display.setCursor(18,50);
  display.println("Room 3 :" + String(T3));
  display.display();

  delay(1000); 
}

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