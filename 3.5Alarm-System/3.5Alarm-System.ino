// 3.5 ALARM SYSTEM
// 3.5 Functionality to alert the alarm and blinks the LED when sensor detects a motion.

// Make sure the pin number match with io16, io23 , io27 you attach on the board.
#define Buzzer 16  // Set the buzzer pin.
#define PIRmotion 23  // Set the PIR mition sensor pin.
#define LED 27  // Set the LED pin.

// Set the setup.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to "9600".
  
  //Set the pins modes.
  pinMode(Buzzer, OUTPUT);  // Set the buzzer as output.
  pinMode(PIRmotion, INPUT);  // Set the PIR motion as input.
  pinMode(LED, OUTPUT);  // Set the LED as output.
}

// The loop functtion run repeatedly forever.
void loop() {

  int ReadValue = digitalRead(PIRmotion);  // Read the value of PIR motion sensor.

  if(ReadValue){  // Hold value from PIRMotion. 

    Serial.println("Someone");  // Print "Someone".
    
    digitalWrite(LED, HIGH);  // LED turning on.

    // Ascending pitch.
    for(int i = 200; i<=1000; i+=10){  // Control the duration.
      tone(Buzzer, i);  // Declare the tone.
      delay(10);  // Delay for 10 microsecond.
    }

    digitalWrite(LED, LOW);  // LED turning off.
    
    // Descending pitch.
    for(int i = 1000; i>=200; i-=10){  // Control the duration.
      tone(Buzzer, i);  // Declare the tone.
      delay(10);  // Delay for 10 microsecond.
    }
  }

  noTone(Buzzer); // Turn off the tone.

  Serial.println("No one");  // Print "No one".

}

// RESULT
// When PIR motion sensor detects persens of human heat, alarm will alert and LED will blinks.