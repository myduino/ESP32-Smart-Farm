// 6.3 INTELLIGENT FEEDING SYSTEM
// 6.4 Function to determines the presence of animals via the distance value. If there is, feeding box will open.

#include <ESP32_Servo.h>  // Import the library for servo control on ESP32 board.

Servo myservo;  // Create a servo object to control a servo.

// Make sure the pin number match with io12, io13, io26 you attach on the board.
#define Trig 12  // Set the trig sensor pin.
#define Echo 13  // Set the echo sensor pin.
#define Servo 26 // Set the servo pin.

int duration, distance; // Variables to store the duration of the pulse and the calculated distance.

// Set the setup.
void setup() {
  Serial.begin(9600);         // Initialize serial communication and set baud rate to "9600".
  pinMode(Trig, OUTPUT);   // Set the trig pin as an output.
  pinMode(Echo, INPUT);    // Set the echo pin as an input.
  myservo.attach(Servo);   // Attach the servo on pin 26 to the servo object.
}

// The loop function run repeatedly forever.
void loop() {
  Serial.println(getDistance());  // Print the distance measured by the ultrasonic sensor.

  // When the distance is detected within 2 to 7 cm, open the feeding box. Otherwise, close it.
  if (getDistance() >= 2 && 7 >= getDistance()) {
    myservo.write(80);       // Rotate the servo to 80 degrees to open the box
    delay(500);              // Wait for 500 milliseconds
  } else {
    myservo.write(180);      // Rotate the servo to 180 degrees to close the box
    delay(500);              // Wait for 500 milliseconds
  }
}

// Function to measure and return the distance detected by the ultrasonic sensor.
float getDistance() {
  digitalWrite(Trig, LOW);      // Set the trig pin is low.
  delayMicroseconds(2);            // Wait for 2 microseconds.

  digitalWrite(Trig, HIGH);     // Set the trig pin high.
  delayMicroseconds(10);           // Wait for 10 microseconds to trigger the sensor.
  digitalWrite(Trig, LOW);      // Set the trig pin low.

  duration = pulseIn(Echo, HIGH); // Measure the duration of the pulse from the echo pin.
  distance = duration / 58;          // Convert the duration into distance in centimeters.
  delay(50);                         // Wait for 50 milliseconds before the next measurement.
  
  return distance;                   // Return the measured distance.
}

// RESULT
// System will opened feeding box when there is object in rage distance between 2cm to 7cm.
// Other than that feeding box will closed.
