#define SPEAKER_PIN 9

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  // Generate a 1kHz square wave on pin D9
  tone(SPEAKER_PIN, 1000);
  delay(1000);               // Keep the tone on for 1 second

  // Stop the tone output
  noTone(SPEAKER_PIN);
  delay(1000);               // Silence for 1 second
}
