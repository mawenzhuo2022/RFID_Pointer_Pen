// Microphone test with LED indication

#define MIC_PIN A0     // Microphone output connected to A0
#define LED_PIN 13     // Small LED on pin 13

void setup() {
  pinMode(LED_PIN, OUTPUT);   // Configure the LED pin as output
  Serial.begin(9600);         // Initialize serial communication for monitoring
}

void loop() {
  // Read the microphone's analog value (range: 0 to 1023)
  int micValue = analogRead(MIC_PIN);

  // Print the microphone reading to the Serial Monitor
  Serial.print("Microphone Reading: ");
  Serial.println(micValue);

  // If the reading is above 500, turn on the LED; otherwise, turn it off
  if (micValue > 600) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // A short delay to avoid flooding the serial monitor
  delay(100);
}
