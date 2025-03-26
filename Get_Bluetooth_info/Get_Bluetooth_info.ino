#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(115200); 

  delay(2000);
  Serial.println("Sending $$$ to enter command mode...");
  BTSerial.print("$$$");
  delay(1000);

  Serial.println("Requesting config info...");
  BTSerial.print("D\r");  // Display current config
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }
}
