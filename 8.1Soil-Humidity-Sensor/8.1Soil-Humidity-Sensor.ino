// 8.1 SOIL HUMIDITY SENSOR
// 8.1 Function to reads the value of soil humidity.

// Make sure the pin number watch with io32 you attach on the board.
#define SoilHumidity 32  // Set the soil humidity sensor pin.

// Set the setup.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to "9600".

  pinMode(SoilHumidity, INPUT);  // Set the steam senor as input.
}

// The loop function run repeatedly forever.
void loop() {

  int ReadValue = analogRead(SoilHumidity);  // Read the value of soil humidity sensor.
  
  Serial.println(ReadValue);  // Print value of steam sensor.
  
  delay(500);  // Delay for 5 millisecond.
}

// RESULT
// Touch the detection area of the sensor with your wet finger.
// Currently detected humidity value will be printed on the monitor.
// value will display in unit Digital-to-Analog(DAC).