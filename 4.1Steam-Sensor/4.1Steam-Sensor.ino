// 4.1 STEAM SENSOR
// 4.1 Function to read the value of steam sensor.

// Make sure the pin number match with io35 you attach on the board.
#define Steam 35  // Set the steam sensor pin.

// Set the setup.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to "9600".

  pinMode(Steam, INPUT);  // Set the steam senor as input.
}

// The loop function run repeatedly forever.
void loop() {

  int ReadValue = analogRead(Steam);  // Read the value of steam sensor.

  Serial.print("Steam Value: ");  // Print "Steam value: ".

  Serial.println(ReadValue);  // Print value of steam sensor.

  delay(500);  // Delay for 5 millisecond.

}

// RESULT
// Steam sensor will read value of steam and monitor will print the value of steam it reads.