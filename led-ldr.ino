const int ldrPin = A0; // Define LDR pin
const int ledPin = 0; // Define LED pin
int ldrValue; // Variable to store LDR value
int thresholdValue = 1300; // Threshold value for LDR

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate
}

void loop() {
  ldrValue = analogRead(ldrPin); // Read LDR value
  Serial.println(ldrValue); // Print LDR value to serial monitor
  
  if (ldrValue < thresholdValue) { // Check if LDR value is below threshold
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
  }
  
  delay(1000); // Wait for 1 second
}
