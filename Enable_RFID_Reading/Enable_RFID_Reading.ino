#include <SoftwareSerial.h>
#include "SparkFun_UHF_RFID_Reader.h"

// Software serial connected to M7E (D2 ← TX, D3 → RX)
SoftwareSerial softSerial(2, 3);
RFID rfid;

// Configuration parameters
#define rfidSerial softSerial
#define rfidBaud 38400
#define moduleType ThingMagic_M7E_HECTO

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial started");

  rfidSerial.begin(rfidBaud);
  delay(100);

  // Initialize the module (no return value)
  rfid.begin(rfidSerial, moduleType);
  Serial.println("RFID module initialized.");

  rfid.setRegion(REGION_NORTHAMERICA);
  rfid.setReadPower(1000); // 10 dBm

  // Start reading (no return value)
  rfid.startReading();
  Serial.println("Reading started!");
}

void loop() {
  if (rfid.check()) {
    byte responseType = rfid.parseResponse();

    if (responseType == RESPONSE_IS_TAGFOUND) {
      byte tagEPCBytes = rfid.getTagEPCBytes();
      Serial.print("Tag EPC: ");
      for (byte i = 0; i < tagEPCBytes; i++) {
        if (rfid.msg[31 + i] < 0x10) Serial.print("0");
        Serial.print(rfid.msg[31 + i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
    else if (responseType == RESPONSE_IS_KEEPALIVE) {
      Serial.println("[Keep-alive] No tag detected.");
    }
    else if (responseType == ERROR_CORRUPT_RESPONSE) {
      Serial.println("[Error] Corrupt response.");
    }
    else if (responseType == RESPONSE_IS_HIGHRETURNLOSS) {
      Serial.println("[Warning] High return loss.");
    }
    else {
      Serial.print("[Unknown response type] Code: ");
      Serial.println(responseType, HEX);
    }
  }

  delay(100); // optional
}
