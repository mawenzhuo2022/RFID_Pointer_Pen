// Define LED pins
const int greenLEDPin = 9;
const int redLEDPin   = 11;
const int blueLEDPin  = 10;

// Define sensor pins (analog input)
const int redSensorPin   = A0;
const int greenSensorPin = A1;
const int blueSensorPin  = A2;

// Variables to store sensor readings
int redSensorValue   = 0;
int greenSensorValue = 0;
int blueSensorValue  = 0;

// Variables to store mapped values (to be written to LEDs)
int redValue   = 0;
int greenValue = 0;
int blueValue  = 0;

void setup() {
  Serial.begin(9600);

  // Set LED pins as output
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  // Read analog sensor values
  redSensorValue   = analogRead(redSensorPin);
  greenSensorValue = analogRead(greenSensorPin);
  blueSensorValue  = analogRead(blueSensorPin);

  // Print each sensor value separately
  Serial.print("Red Sensor Raw Value: ");
  Serial.println(redSensorValue);
  Serial.print("Green Sensor Raw Value: ");
  Serial.println(greenSensorValue);
  Serial.print("Blue Sensor Raw Value: ");
  Serial.println(blueSensorValue);

  // Print raw sensor values in one line
  Serial.print("Raw Sensor Values \t Red: ");
  Serial.print(redSensorValue);
  Serial.print("\t Green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);

  // Map sensor values (0-1023) to LED brightness range (0-255)
  redValue   = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue  = blueSensorValue / 4;

  // Print mapped values separately
  Serial.print("Red Mapped Value: ");
  Serial.println(redValue);
  Serial.print("Green Mapped Value: ");
  Serial.println(greenValue);
  Serial.print("Blue Mapped Value: ");
  Serial.println(blueValue);

  // Print mapped values in one line
  Serial.print("Mapped Sensor Values \t Red: ");
  Serial.print(redValue);
  Serial.print("\t Green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  // Write mapped values to corresponding LEDs to adjust brightness
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

  // Delay to observe changes
  delay(1000);
}
