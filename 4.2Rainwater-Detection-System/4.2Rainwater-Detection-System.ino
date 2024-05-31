// 4.2 RAINWATER DETECTION SYSTEM
// 4.2 Function to detect value reaches the set threshold, it indicates that it is raining, and the buzzer alarms.


#define Steam 35  // Set the steam sensor pin.
#define Buzzer 16  // Set the buzzer sensor pin.

// Set the setup.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to "9600".

  pinMode(Steam, INPUT);  // Set the steam sensor as input.
  
  pinMode(Buzzer, OUTPUT);  // Set the buzzer as input.

}

// The loop function run repeatedly forever.
void loop() {

  int ReadValue = analogRead(Steam);  //Read the value of steam sensor.

  Serial.print("Steam Value: ");  // Print "Steam value: ".

  Serial.println(ReadValue);  // Print value of steam sensor.

  if(ReadValue >= 800 && 2000 > ReadValue){  // Determine whether the detected value is within 800~2000.
    
    for (int i = 0; i < 3; i++) {  // Execute for 3 times.

      tone(Buzzer, 200);  // Produce a tone frequency of 200Hz.

      delay(100);  // Delay for 1 millisecond.

      noTone(Buzzer);  // Turn off the tone.

      delay(100);  // Delay for 1 millisecond.
    }
  }
  
  else if (ReadValue >= 2000 && 4000 >= ReadValue) {  // Determine whether the detected value is within 2000~4000.

    for (int i = 0; i < 3; i++) {  // Execute for 3 times.
    
      tone(Buzzer, 400);  // Produce a tone frequency of 400Hz.
      
      delay(100);  // Delay for 1 millisecond.

      noTone(Buzzer);  // Turn off the tone.

      delay(100);  // Delay for 1 millisecond.
    
    }
  }

  else if (ReadValue > 4000) {  // Determine whether the detected value is greater than 4000.

    for (int i = 0; i < 3; i++) {  // Execute for 3 times.
    
      tone(Buzzer, 600);  // Produce a tone frequency of 600Hz.
      
      delay(100);  // Delay for 1 millisecond.

      noTone(Buzzer);  // Turn off the tone.

      delay(100);  // Delay for 1 millisecond.
    
    }
  }

  noTone(Buzzer);  // Turn off the tone.

  delay(500); // Delay for 5 millisecond.

}

// DANGER
// System will read rainwater value from Steam sensor. The greater the detected value is,
// louder the sound emitted by the buzzer.