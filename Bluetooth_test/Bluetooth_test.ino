//receiver

#include <SoftwareSerial.h>

// Define Bluetooth module communication pins
#define BT_RX 10   // Bluetooth module TX connected to Arduino RX
#define BT_TX 11   // Bluetooth module RX connected to Arduino TX
#define LED 13     // LED indicator connected to Arduino pin 13

// Create a SoftwareSerial instance for Bluetooth communication
SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup() {
  pinMode(LED, OUTPUT);        // Set LED pin as output
  Serial.begin(9600);          // Initialize serial communication with the PC
  BTSerial.begin(9600);        // Initialize Bluetooth communication
  Serial.println("Bluetooth Receiver Initialized. Waiting for data...");
}

void loop() {
  if (BTSerial.available()) {  // Check if there is incoming Bluetooth data
    digitalWrite(LED, HIGH);   // Turn on LED when data is received
    char data = BTSerial.read();
    Serial.print("Received: ");
    Serial.println(data);
    delay(100);
  } else {
    digitalWrite(LED, LOW);    // Turn off LED when no data is received
  }
}


//sender

#include <SoftwareSerial.h>

// Define Bluetooth module communication pins
#define BT_RX 10   // Bluetooth module TX connected to Arduino RX
#define BT_TX 11   // Bluetooth module RX connected to Arduino TX

// Create a SoftwareSerial instance for Bluetooth communication
SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup() {
  Serial.begin(9600);         // Initialize serial communication with the PC
  BTSerial.begin(9600);       // Initialize Bluetooth communication (ensure the baud rate matches the module)
  Serial.println("Bluetooth Sender Initialized. Sending data...");
}

void loop() {
  // Periodically send string data via Bluetooth
  BTSerial.println("Hello from Arduino");
  Serial.println("Data sent: Hello from Arduino");
  delay(2000);  // Send data every 2 seconds
}

