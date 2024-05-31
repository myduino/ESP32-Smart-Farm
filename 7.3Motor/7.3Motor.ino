// 7.3 Motor
// 7.3 function to controls the fan speed via PWM.

#define Motor1 19  // Set the Motor1 pin (IN+).
#define Motor2 18  // Set the Motor2 pin (IN-).

// Set the setup.
void setup() {

  pinMode(Motor1, OUTPUT);  // Set MotorPin1 as an output.
  
  pinMode(Motor2, OUTPUT);  // Set MotorPin2 as an output.

  // Set PWM output to adjust the speed of motor.
  ledcSetup(1, 1200, 8);        //Set frequency of LEDC Channel 1 to 1200, PWM resolution to 8, so duty cycle = 256
  ledcAttachPin(Motor1, 1);  //Bound LEDC Channel 1 to the specified left motor pin gpio19 to output.
  
  ledcSetup(3, 1200, 8);        //Set frequency of LEDC Channel 3 to 1200, PWM resolution to 8, so duty cycle = 256
  ledcAttachPin(Motor2, 3);  //Bound LEDC Channel 3 to the specified left motor pin gpio18 to output.
}

// The loop function run repeatedly forever.
void loop() {

  //Turn left
  ledcWrite(1, 70);  // Set duty cycle of LEDC Channel 1 to 70, stopping the first motor pin.
  ledcWrite(3, 0);   // Set duty cycle of LEDC Channel 3 to 0, stopping the first motor pin.

  delay(2000);  // Set the delay for 2 second.

  // Stop
  // WHY STOP: Prevent an excessive current at the moment of reversal. Otherwise, a forced reset may occur due to insufficient power supply on the development board.
  delay(200);  // Set the delay for 200 millisecond.
  ledcWrite(1, 0);  // Set duty cycle of LEDC Channel 1 to 0, stopping the first motor pin.
  ledcWrite(3, 0);  // Set duty cycle of LEDC Channel 3 to 0, stopping the first motor pin.
  delay(200);       // Set delay for 2 milliseconds.
  
  //Turn right // Set the delay for 200 millisecond.
  ledcWrite(1, 0);  // Set duty cycle of LEDC Channel 1 to 0, stopping the first motor pin.
  ledcWrite(3, 70); // Set duty cycle of LEDC Channel 3 to 70, stopping the first motor pin.

  delay(2000);  // Set delay for 2 seconds.
  
  //Stop
  delay(200); // Set the delay for 200 millisecond.
  ledcWrite(1, 0); // Set duty cycle of LEDC Channel 1 to 0, stopping the first motor pin.
  ledcWrite(3, 0); // Set duty cycle of LEDC Channel 3 to 0, stopping the first motor pin.
  delay(200); // Set the delay for 200 millisecond.
  
}

// RESULT
// Motor will roatets left and right every 2 seconds.
// NOTE
// Don't stop the stop moving fan by force it may cause motor problem later.