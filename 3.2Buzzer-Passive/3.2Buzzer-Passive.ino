// 3.2 BUZZER PASSIVE
// 3.2 This function for emits sounds, it can be reminder or an alarm.

// Make sure the pin number match with io16 you attach on the board.
#define Buzzer 16  //Define the buzzer pin

// Set the setup.
void setup() {
  
  pinMode(Buzzer, OUTPUT);  // Set the buzzer pin as output.

}

// The loop function runs repeatedly forever.
void loop() {

  digitalWrite(Buzzer, HIGH);  // HIGH means buzzer turn on.
  
  delayMicroseconds(500);  // Delay for 5 millisecond.
  
  digitalWrite(Buzzer, LOW);  // LOW means buzzer turn off.
  
  delayMicroseconds(500);  // Delay for 5 millisecond.

}

// RESULT
// Buzzer will emit sound base on duration delay set.
