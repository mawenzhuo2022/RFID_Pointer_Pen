#include <SoftwareSerial.h>

// D2 = RX, D3 = TX
SoftwareSerial btSerial(2, 3);

void setup() {
  Serial.begin(9600);        // Start USB serial communication with PC
  btSerial.begin(115200);    // Start Bluetooth serial communication

  Serial.println("Bluetooth serial bridge ready.");
}

void loop() {
  // Read from Bluetooth and send to PC
  if (btSerial.available()) {
    char c = btSerial.read();
    Serial.print("From Bluetooth: ");
    Serial.println(c);
  }

  // Read from PC and send to Bluetooth
  if (Serial.available()) {
    char c = Serial.read();
    btSerial.write(c);
  }
}
