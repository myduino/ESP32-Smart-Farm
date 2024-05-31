// 6.1 SERVO
// 6.1 Function to control servo via PWM to open and close the feeding box.

// Import the library of servo. NOTE: Make sure the file name same as the in library.
#include <ESP32_Servo.h>

Servo myservo;  // Create servo object to control a servo.
                
int pos = 0;  // Variable to store the servo position.

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Make sure the pin number match with io26 you attach on the board.
int servoPin = 26;

// Set the setup.                
void setup() {

  Serial.begin(9600);  // Start serial communication with baud rate "9600".

  myservo.attach(servoPin);  // Attach the servo on pin 26 to the servo object

  myservo.write(180);  // Move the servo to initial position 180 degrees.

  delay(2000);  // Delay for 2 second.
}

// The loop function run repeatedly forever.
void loop() {

  for (pos = 80; pos <= 179; pos += 1) {  // Goes from 0 degrees to 80 degrees.
    
    myservo.write(pos);  // Tell servo to go to position in variable 'pos'.
    delay(15);  // Waits 15 microsecond for the servo to reach the position.
  }

  for (pos = 180; pos >= 81; pos -= 1) { // Goes from 80 degrees to 0 degrees.

    myservo.write(pos);  // Tell servo to go to position in variable 'pos'.
    delay(15);  // Waits 15 microsecond for the servo to reach the position.
  }
}

// RESULT
// The feeding box is slowly opened and then closed.

// ATTENTION
// Do not put your finger into the box to avoid nipping.
// DO not block the door with something to avoid damaging servo.