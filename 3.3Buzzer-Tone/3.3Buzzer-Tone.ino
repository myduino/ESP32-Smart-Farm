// 3.3 BUZZER TONE
// 3.3 Function for buzzer tone is just like others with the same purpose but the tone is controlled.

// Make sure the pin number match with io16 you attach on the board.
const int Buzzer = 16;   // Set the buzzer pin

// Set the setup.
void setup() {

  pinMode(Buzzer, OUTPUT); // Set the buzzer pin as output.

}

// The loop function runs repeatedly forever.
void loop() {

  // Play individual tones with delays in between.
    tone(Buzzer, 532);  // Play the tone "C2".
    delay(100);

    tone(Buzzer, 587);  // Play the tone "D3".
    delay(100);

    tone(Buzzer, 659);  // Play the tone "E3".
    delay(100);

    // Play an alarm like sound
    // Ascending pitch
    for(int i = 200; i<=1000; i+=10){  // Control the duration.
      tone(Buzzer, i);  // Declare the tone.
      delay(10);  // Delay for 10 microsecond.
    }

    // Descending pitch
    for(int i = 1000; i>=200; i-=10){  // Control the duration.
      tone(Buzzer, i);  // Declare the tone.
      delay(10);  // Delay for 10 microsecond.
    }

    noTone(Buzzer); // Trun off the tone.

}

