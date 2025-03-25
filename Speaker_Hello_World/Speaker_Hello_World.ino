#include <Arduino.h>
#include <Talkie.h>
#include <Vocab_US_TI99.h>  

Talkie voice;
const int ledPin = 8;

void flashLED(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
    digitalWrite(ledPin, LOW);
    delay(delayTime);
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println(F("Starting LED flash between speech segments..."));
}

void loop() {
  voice.say(spt_HELLO);
  
  flashLED(5, 100);
  
  voice.say(spt_WORDS);
  
  flashLED(5, 100);
  
  delay(5000);
}
