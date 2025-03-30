#include <SoftwareSerial.h>

// Define Bluetooth module pins
int bluetoothTx = 2;  // TX-O pin of Bluetooth Mate, Arduino pin D2
int bluetoothRx = 3;  // RX-I pin of Bluetooth Mate, Arduino pin D3

SoftwareSerial bluetooth = SoftwareSerial(bluetoothTx, bluetoothRx); // Create a software serial port for Bluetooth communication

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  // Initialize both Serial Monitor and Bluetooth serial port
  Serial.begin(9600);          // Start serial communication at 9600 bps with the computer
  Serial.println("Starting setup...");

  bluetooth.begin(115200);     // Start communication with the Bluetooth module at 115200 bps (default baud rate for RN-42)
  Serial.println("Bluetooth module initialized at 115200 bps.");

  bluetooth.println("ST,255"); // Disable configuration timer


  bluetooth.print("$");       // Enter Bluetooth command mode by sending "$$$" one character at a time
  bluetooth.print("$");
  bluetooth.print("$");
  Serial.println("Sent '$$$' to enter command mode.");
  
                 
  Serial.println("Waiting for Bluetooth module to switch to command mode...");
  delay(1050);   // Wait for the Bluetooth module to switch to command mode

  bluetooth.println("U,9600,N");   // Change the baud rate to 9600 bps temporarily (for easier communication)
  Serial.println("Changed Bluetooth baud rate to 9600 bps.");

  delay(100);                     // Wait for the baud rate change to take effect 
  Serial.println("Waiting for baud rate change to take effect...");

  bluetooth.begin(9600);     // Re-initialize Bluetooth serial communication at 9600 bps (after the change)
  Serial.println("Bluetooth module re-initialized at 9600 bps.");

  Serial.println("Bluetooth setup complete, you can start sending and receiving data.");
}

void loop() {
  // Check if the Bluetooth module has any data to send to the Serial Monitor
  if (bluetooth.available()) {
    char incomingByte = bluetooth.read();  // Read the data from Bluetooth
    Serial.print("Received from Bluetooth: ");
    Serial.println(incomingByte);            // Print the data to Serial Monitor
  }

  // Check if the Serial Monitor has any data to send to the Bluetooth module
  if (Serial.available()) {
    char outgoingByte = Serial.read();     // Read the data from Serial Monitor
    bluetooth.print(outgoingByte);         // Send the data to Bluetooth
    Serial.print("Sent to Bluetooth: ");
    Serial.println(outgoingByte);          // Print what was sent to Bluetooth
  }
}
