/*
   This sketch alternates between two states:
   1. Speaker plays a tone (440 Hz) and the LED flashes.
   2. Speaker is silent and the LED stays off.

   The speaker is connected to digital pin 7.
   The LED is connected to digital pin 8.
*/

const int speakerPin = 7; // Speaker connected to digital pin 7
const int ledPin = 8;     // LED connected to digital pin 8

void setup() {
  // Initialize the speaker and LED pins as outputs.
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // ---- State 1: Speaker on, LED flashing ----
  
  // Start playing a 440 Hz tone on the speaker
  tone(speakerPin, 440);
  
  // Flash the LED for 2 seconds while the tone is playing
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    digitalWrite(ledPin, HIGH); // Turn LED on
    delay(100);                 // Wait 100 ms
    digitalWrite(ledPin, LOW);  // Turn LED off
    delay(100);                 // Wait 100 ms
  }
  
  // ---- State 2: Speaker off, LED off ----
  
  // Stop the tone on the speaker
  noTone(speakerPin);
  
  // Ensure the LED is off
  digitalWrite(ledPin, LOW);
  
  // Wait for 2 seconds before repeating
  delay(2000);
}
