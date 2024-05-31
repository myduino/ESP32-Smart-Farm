// 1.2 LED-PMW (Pulse Width Modulation)
// 1.2 Code purpose to run/test LED control the brightness of LED.

// Make sure the pin number match with the io27 you attach on the board.
#define LED 27  // Define the pin number for the LED as 27.

// Set the Setup here.
void setup(){

  pinMode(LED, OUTPUT);  // Set the LED pin as an output.
}

//  The loop function runs repeatedly forever.
void loop(){

  for(int i=0; i<255; i++){  // Loop from 0 to 254 to gradually increase brightness.

    analogWrite(LED, i);  // Set the LED brightness using PWM.

    delay(3);  // Delay to observe the change in brightness.
  }
  for(int i=255; i>0; i--){  // Loop from 255 to 1 to gradually decrease brightness.
  
    analogWrite(LED, i);  // Set the LED brightness using PWM.

    delay(3);  // Delay to observe the change in brightness.
  }
}

// RESULT
// LED(27) will increase up and down brightness of LED.