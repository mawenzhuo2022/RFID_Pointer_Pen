#include <SoftwareSerial.h>

SoftwareSerial silverMateSerial(2, 3); // D2 = RX, D3 = TX

unsigned long lastAT = 0;
unsigned long lastReceive = 0;
const unsigned long AT_INTERVAL = 10000; // Send "AT" every 10 seconds

void setup() {
  Serial.begin(9600);
  silverMateSerial.begin(115200);  // Default baud rate for RN-42

  delay(2000); // Wait 2 seconds for module startup
  Serial.println("Sending $$$ to enter CMD mode...");
  silverMateSerial.print("$$$");   // Attempt to enter command mode
  lastAT = millis();
}

void loop() {
  // Periodically send "AT" command
  if (millis() - lastAT > AT_INTERVAL) {
    Serial.println("[SEND] AT");
    silverMateSerial.println("AT");
    lastAT = millis();
  }

  // Print received characters with HEX and interval information
  if (silverMateSerial.available()) {
    byte c = silverMateSerial.read();
    unsigned long now = millis();

    Serial.print("[RECV] Char: ");
    if (c >= 32 && c <= 126) {
      Serial.print((char)c);
    } else {
      Serial.print(".");
    }

    Serial.print("  HEX: 0x");
    if (c < 0x10) Serial.print("0");
    Serial.print(c, HEX);
    Serial.print("  (+");
    Serial.print(now - lastReceive);
    Serial.println(" ms)");

    lastReceive = now;
  }
}
