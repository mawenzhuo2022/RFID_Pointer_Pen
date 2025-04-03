#include <SoftwareSerial.h>

// D2 = RX, D3 = TX
SoftwareSerial btSerial(2, 3);

String inputString = "";
bool stringComplete = false;

void setup() {
  pinMode(13, OUTPUT);          // Onboard or external LED on D13
  digitalWrite(13, LOW);        // Make sure it's off

  Serial.begin(9600);           // Serial monitor
  btSerial.begin(115200);       // ✅ Match this to your module's actual baud rate

  Serial.println("Bluetooth LED control ready.");
  btSerial.println("Bluetooth LED control ready.");
}

void loop() {
  // Read characters from Bluetooth
  while (btSerial.available()) {
    char c = btSerial.read();

    // Show received character
    Serial.print("Received: ");
    Serial.print(c);
    Serial.print(" (ASCII ");
    Serial.print((int)c);
    Serial.println(")");

    // Echo character to Bluetooth
    btSerial.print("Char: ");
    btSerial.println(c);

    // Detect end of command
    if (c == '\n' || c == '\r') {
      stringComplete = true;
    } else {
      inputString += c;
    }
  }

  // Process full command when received
  if (stringComplete) {
    // Step 1: Trim whitespace
    String trimmed = inputString;
    trimmed.trim();

    // Step 2: Remove any non-printable characters
    String clean = "";
    for (int i = 0; i < trimmed.length(); i++) {
      char ch = trimmed.charAt(i);
      if (ch >= 32 && ch <= 126) {  // Keep only printable ASCII
        clean += ch;
      }
    }

    // Log full command
    Serial.print("Cleaned command: ");
    Serial.println(clean);
    btSerial.print("You sent: ");
    btSerial.println(clean);

    // Step 3: Command handling
    if (clean == "LED_ON") {
      digitalWrite(13, HIGH);
      Serial.println("LED turned ON");
      btSerial.println("LED is ON");
    } else if (clean == "LED_OFF") {
      digitalWrite(13, LOW);
      Serial.println("LED turned OFF");
      btSerial.println("LED is OFF");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(clean);
      btSerial.println("Unknown command");
    }

    // Reset input buffer
    inputString = "";
    stringComplete = false;
  }

  // Optional: echo USB serial input to Bluetooth
  if (Serial.available()) {
    char c = Serial.read();
    btSerial.write(c);
  }
}
