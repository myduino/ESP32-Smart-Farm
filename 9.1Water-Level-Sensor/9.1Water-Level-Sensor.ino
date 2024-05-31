// 9.1 WATER LEVEL SENSOR
// 9.1 Function to reads the value of water level of the container.

#define WaterLevelPin 33  // Define the pin for the water level sensor as GPIO 33.

void setup() {
  Serial.begin(9600);  // Initialize serial communication and set the baud rate to 9600.
  pinMode(WaterLevelPin, INPUT);  // Set the water level pin as an input.
}

void loop() {
  int ReadValue = analogRead(WaterLevelPin);  // Read the analog value from the water level sensor.
  Serial.println(ReadValue);  // Print the read value to the serial monitor.
  delay(500);  // Wait for 500 milliseconds before the next reading.
}

// RESULT
// Touch the detection area of the sensor with your wet finger.
// The currently detected value will be printed on the monitor.
// value will display in unit Digital-to-Analog(DAC).