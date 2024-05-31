// 2.1 PHOTOCECLL SENSOR
// 2.1 Code purpose is to detect light brightness and display the value will be.

// Make sure the pin number match with io34 you attach on the board.
#define Photocecll 34  // Define the pin number for the photoresistor as 34.

// Set the setup here.
void setup() {
  
  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.
  
  pinMode(Photocecll, INPUT);  // Set the photoresistor pin as input.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = analogRead(Photocecll);  // Read the value of photoresistor.
  
  Serial.print("Photocecll value: ");  // Print the value. 

  Serial.println(ReadValue);  // Print the value of photoresistor input. 

  delay(500);  // Delay for 5 Milisecond.

}

// RESULT
// Serial monitor will display:
// "Photocecll value: [value of light brightness]"
// Brightness light detects by sensor the greater value output will be.
// ESP32 board is 12-bit ADC, whose detection range is within 0~4095. 