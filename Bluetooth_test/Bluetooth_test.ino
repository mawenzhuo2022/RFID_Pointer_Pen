#include <SoftwareSerial.h>

// 在 Arduino Uno 上，指定 D10 作为 SoftwareSerial RX 引脚（连到蓝牙 TX），
// 指定 D11 作为 SoftwareSerial TX 引脚（连到蓝牙 RX）
SoftwareSerial BTSerial(10, 11);

void setup() {
  // 1. 打开硬件串口(Arduino自带串口) 用于调试输出
  Serial.begin(9600);
  while (!Serial) {
    ; // 等待串口就绪，仅在需要时使用
  }
  
  // 2. 打开蓝牙对应的SoftwareSerial串口
  //    波特率要与 Bluetooth Mate 模块默认波特率相匹配
  //    常见默认值：9600, 38400, 或 115200（需参考模块资料）
  BTSerial.begin(9600);

  Serial.println("==== Bluetooth Mate test begin ====");
  Serial.println("Ready to pair with PC via Bluetooth");
}

void loop() {
  // 从 Bluetooth Mate 读取数据并转发到串口监视器
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }

  // 从串口监视器读取数据并转发到 Bluetooth Mate
  if (Serial.available()) {
    char c = Serial.read();
    BTSerial.write(c);
  }
}
