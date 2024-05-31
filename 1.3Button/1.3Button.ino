// 1.3 BUTTON
// 1.3 Code purpose is for when user click/hold the button the serial monitor will print value.

// Make sure the pin number match with the io5 you attach on the board.
#define Button 5 // Define the pin number for the button as 5.

// Set the Setup here.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.
  
  pinMode(Button, INPUT);  // Set the button pin as input.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = digitalRead(Button);  // Read the digital value from the button pin.
  
  Serial.print("The current status of the button is : ");  // Print the current status of the button to the serial port.
  
  Serial.println(ReadValue);  // Print default value '0'.
  
  delay(500);  // Delay for 500 milliseconds

}

// RESULT
// When user click/hold the button the serial monitor will display:
// The current status of the button is : 0
// if nothing action taken to the button then the serial monitor will display:
// The current status of the button is : 1