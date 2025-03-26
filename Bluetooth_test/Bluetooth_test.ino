#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(115200);

  delay(2000);
  Serial.println("== Nuclear Reset ==");

  BTSerial.print("$$$"); delay(1000);

  // 保守全设置
  BTSerial.print("SF,1\r"); delay(1000);   // 出厂设置
  BTSerial.print("SN,BT-TEST\r"); delay(500);  // 设置名字
  BTSerial.print("SM,0\r"); delay(500);   // 设置为可发现、可配对
  BTSerial.print("SA,1\r"); delay(500);   // 设置为从设备（Slave）
  BTSerial.print("SP,1234\r"); delay(500); // 设置配对码
  BTSerial.print("R,1\r"); delay(1000);   // 重启模块
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }
}
