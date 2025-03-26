#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(115200); 

  delay(1000);
  Serial.println("Force Resetting Bluetooth Mate...");

  BTSerial.print("$$$");     delay(500);
  BTSerial.print("SF,1\r");  delay(1000);
  BTSerial.print("SN,BT-TEST\r"); delay(500);
  BTSerial.print("SM,0\r");  delay(500);
  BTSerial.print("SA,1\r");  delay(500);
  BTSerial.print("SP,1234\r"); delay(500);
  BTSerial.print("R,1\r");   delay(1000);
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }
}
