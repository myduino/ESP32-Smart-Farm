// 1.1 LED-BLINK
// 1.1 Code purpose to run/test LED turn on and off in 1 second delay.

// Make sure the pin number match with the io27 you attach on the board.
#define LED 27  // Define the pin number of the LED as 27.

// Set the Setup here.
void setup() {
  
  pinMode(LED, OUTPUT);  // Set the LED pin as output. 

}

// The loop function runs repeatedly forever.
void loop() {

  digitalWrite(LED, HIGH);  // Turn the LED on by making the voltage HIGH.  
  
  delay(1000);  // Delay for 1 second.              
  
  digitalWrite(LED, LOW);  // Turn the LED off by making the voltage LOW.
  
  delay(1000);  // Delay for 1 second.     

}

// RESULT
// LED(27) will turn on and off after 1 second delay.
