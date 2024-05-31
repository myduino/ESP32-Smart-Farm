// 6.2 ULTRASONIC SENSOR
// 6.2 Function is to reads the distance value detected by ultrasonic.

// Make sure the pin number match with io12, io13 you attach on the board.
#define Trig 12  // Set the trig sensor pin.
#define Echo 13  // Set the Echo sensor pin.

int duration, distance;

// Set the setup.
void setup(){

  Serial.begin(9600);  // Initialize serial communication and set baud rate to "9600".

  pinMode(Trig, OUTPUT);  //set trig sensor as output.

  pinMode(Echo, INPUT);   //set echo sensor as input.

}

// The loop function run repeatedly forever.
void loop() {
  digitalWrite(Trig, LOW);       // Ensure the trig pin is low.
  delayMicroseconds(2);          // Wait for 2 microseconds.
  
  digitalWrite(Trig, HIGH);      // Set the trig pin high.
  delayMicroseconds(10);         // Wait for 10 microseconds to trigger the sensor.
  
  digitalWrite(Trig, LOW);       // Set the trig pin low.
  
  duration = pulseIn(Echo, HIGH); // Read the echo pin, returns the duration of the pulse in microseconds.
  
  distance = duration / 58;      // Convert the duration into distance in centimeters.
  
  delay(50);                     // Wait for 50 milliseconds before the next measurement.

  Serial.print("Distance: ");    // Print the label "Distance:" to the serial monitor.
  Serial.print(distance);        // Print the distance value to the serial monitor.
  Serial.println(" cm");         // Print " cm" and move to the next line on the serial monitor.
}

// RESULT
// Ultrasonic sensor will detected object distance in the range and display with the cm measurument.