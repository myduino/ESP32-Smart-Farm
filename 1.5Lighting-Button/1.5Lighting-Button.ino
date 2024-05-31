// 1.5 LIGHTING BUTTON
// 1.5 Code purpose is to get input from the button and output using LED light.

// Make sure the pin number match with the io5, io27 you attach on the board.
#define Button 5  // Define the pin number for the button as 5.
#define LED  27  // Define the pin number for the button as 27.

int value = 0;  // Define a value to detect button status.

// Set the setup here.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.
  
  pinMode(Button,INPUT);  // Set the button pin as input.
  
  pinMode(LED,OUTPUT);  // Set the LED pin as output.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = digitalRead(Button);  // Define a value as the read button value
  
  if (ReadValue == 0) {  //Detect whether the button is pressed
    
    delay(10);  // Debounce the button to avoid false triggers.

    if (ReadValue == 0) {  // Check if the button is still pressed after debounce.

      value = !value;  // Toggle the value of 'value' to indicate the button status change.
      
      //Detect the button status, press once to light up LED, press again to turn off LED, in a loop.
      if(value) {
        digitalWrite(LED, HIGH);  // HIGH means LED light on.
      }
      else{
        digitalWrite(LED, LOW);  // LOW means LED light off.
      }
    }

    // Detect the button status again.
    while (digitalRead(Button) == 0);  // Detect the button status again. 

  }
}

// RESULT
// Default state when no press on the button so LED is off.
// Press the button once then LED will lights on.
// This action will continue looping.