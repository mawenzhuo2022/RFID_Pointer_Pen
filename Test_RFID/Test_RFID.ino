#include <SoftwareSerial.h>
#include "SparkFun_UHF_RFID_Reader.h"

// Setup software serial (D2 = RX, D3 = TX)
SoftwareSerial softSerial(2, 3); // Arduino RX ← M7E TX, Arduino TX → M7E RX

RFID rfidModule;

// Use software serial for RFID
#define rfidSerial softSerial
#define rfidBaud 38400         // Use 38400 for software serial
#define moduleType ThingMagic_M7E_HECTO // Your module is M7E

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to open

  Serial.println(F("Initializing M7E module..."));

  // Initialize RFID module
  rfidModule.begin(rfidSerial, moduleType);

  // Set region and power
  rfidModule.setRegion(REGION_NORTHAMERICA); // Change to REGION_CHINA if needed
  rfidModule.setReadPower(500); // 5.00 dBm; increase if needed, max 2700

  Serial.println(F("Starting to read tags..."));

  // Begin continuous reading immediately
  rfidModule.startReading();
}

void loop() {
  Serial.println(rfidModule.check());
  if (rfidModule.check() == true) {
    byte responseType = rfidModule.parseResponse();

    if (responseType == RESPONSE_IS_TAGFOUND) {
      int rssi = rfidModule.getTagRSSI();
      long freq = rfidModule.getTagFreq();
      long timeStamp = rfidModule.getTagTimestamp();
      byte tagEPCBytes = rfidModule.getTagEPCBytes();

      Serial.print(F("Tag Found → RSSI: "));
      Serial.print(rssi);
      Serial.print(F(" dBm | Freq: "));
      Serial.print(freq);
      Serial.print(F(" kHz | Time: "));
      Serial.print(timeStamp);
      Serial.print(F(" ms | EPC: "));

      for (byte x = 0; x < tagEPCBytes; x++) {
        if (rfidModule.msg[31 + x] < 0x10) Serial.print(F("0"));
        Serial.print(rfidModule.msg[31 + x], HEX);
        Serial.print(F(" "));
      }
      Serial.println();
    }
    else if (responseType == RESPONSE_IS_KEEPALIVE) {
      Serial.println(F("[Keep-alive] No tag detected yet..."));
    }
    else if (responseType == ERROR_CORRUPT_RESPONSE) {
      Serial.println(F("[Error] Corrupt response received."));
    }
    else if (responseType == RESPONSE_IS_HIGHRETURNLOSS) {
      Serial.println(F("[Warning] High return loss, check antenna connection."));
    }
    else {
      Serial.println(F("[Unknown Response]"));
    }
  }
}
