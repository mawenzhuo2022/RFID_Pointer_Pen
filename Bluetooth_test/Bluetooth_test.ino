#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(115200);

  delay(2000);
  Serial.println("== Nuclear Reset ==");

  BTSerial.print("$$$"); delay(1000);

  BTSerial.print("SF,1\r"); delay(1000);  
  BTSerial.print("SN,BT-TEST\r"); delay(500);  // set name
  BTSerial.print("SM,0\r"); delay(500);   // set to can be found
  BTSerial.print("SA,1\r"); delay(500);   // set as border device
  BTSerial.print("SP,1234\r"); delay(500); // set connection code
  BTSerial.print("R,1\r"); delay(1000);   // restart board
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }
}
