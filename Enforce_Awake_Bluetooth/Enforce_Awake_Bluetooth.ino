#include <SoftwareSerial.h>

SoftwareSerial silverMateSerial(2, 3); // D2 = RX, D3 = TX

unsigned long lastTrigger = 0;
unsigned long triggerInterval = 3000; // Wake up every 3 seconds
int triggerStage = 0;

unsigned long lastReceive = 0;

void setup() {
  Serial.begin(9600);
  silverMateSerial.begin(115200); // Default baud rate for RN-42
  delay(2000);

  Serial.println("=== RN-42 Wake-Up Script Started ===");
}

void loop() {
  unsigned long now = millis();

  // Wake up every 3 seconds, send different commands in a loop
  if (now - lastTrigger > triggerInterval) {
    switch (triggerStage % 4) {
      case 0:
        Serial.println("[SEND] $$$");
        silverMateSerial.print("$$$");
        break;
      case 1:
        Serial.println("[SEND] +++");
        silverMateSerial.print("+++");
        break;
      case 2:
        Serial.println("[SEND] AT");
        silverMateSerial.println("AT");
        break;
      case 3:
        Serial.println("[SEND] Rubbish");
        silverMateSerial.write((uint8_t)0xF0);
        silverMateSerial.write((uint8_t)0x00);
        silverMateSerial.write((uint8_t)0xFF);
        break;
    }
    triggerStage++;
    lastTrigger = now;
  }

  // Print data received from the module
  if (silverMateSerial.available()) {
    byte c = silverMateSerial.read();
    Serial.print("[RECV] Char: ");
    if (c >= 32 && c <= 126) {
      Serial.print((char)c);
    } else {
      Serial.print(".");
    }

    Serial.print("  HEX: 0x");
    if (c < 0x10) Serial.print("0");
    Serial.print(c, HEX);

    unsigned long now = millis();
    Serial.print("  (+");
    Serial.print(now - lastReceive);
    Serial.println(" ms)");

    lastReceive = now;
  }
}
