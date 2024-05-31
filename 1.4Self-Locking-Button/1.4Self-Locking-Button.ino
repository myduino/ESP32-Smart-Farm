// 1.4 SELF LOCKING BUTTON
// 1.4 Code purpose is to show what output will display after button been clicked.

// Make sure the pin number match with the io5 you attach on the board.
#define Button 5  // Define the pin number for the button as 5.

int value = 0;  // Define a variable to store the status of the button.

//  Set the setup here.
void setup() {
  
  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.
 
  pinMode(Button, INPUT);  // Set the button pin as input.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = digitalRead(Button);  // Read the digital value from the button pin.
  
  if (ReadValue == 0) { // Check if the button is pressed.
    
    delay(10);  // Debounce the button to avoid false triggers.
    
    if (ReadValue == 0) {  // Check if the button is still pressed after debounce.
      
      value = !value;  // Toggle the value of 'value' to indicate the button status change.
      
      Serial.print("The current status of the button is : ");  // Print the current status of the button to the serial port.
      
      Serial.println(value);  // Print 'value'.

    }

    // Wait until the button is released
    while (digitalRead(Button) == 0);  // Continue loop if the button is still pressed, exit loop if released

  }
}

// RESULT
// Current status of the button before click will be '0'. (no output will display in serial monitor)
// When user click the button once the serial monitor will display:
// The current status of the button is : 1
// The next click it will set the loop to '0'.