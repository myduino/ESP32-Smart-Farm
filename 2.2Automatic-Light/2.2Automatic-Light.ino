// 2.2 PHOTOCECLL SENSOR
// 2.2 Code purpose is to detect light brightness and display the value will be.

// Make sure the pin number match with io34, io27 you attach on the board.
#define Photocecll 34  //Define the pin number for the photoresistor as 34.
#define LED 27  //Define the pin number for the LED as 34.

// Set the setup here.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.
   
  pinMode(Photocecll, INPUT);  // Set the photoresistor pin as input.
  
  pinMode(LED, OUTPUT);  // Set the LED pin as output.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = analogRead(Photocecll);  // Read the value of the photoresistor.

  Serial.print("Photocecll value: ");  // Print the value.

  Serial.println(ReadValue);  // Print the value of photoresistor input. 

  if(ReadValue >= 800) {  // If the value of the photoresistor above 800, LED turns off.
    digitalWrite(LED, LOW);  // LOW means LED turning off lights.
    Serial.println("LED OFF");  // Print "LED OFF"
  }

  else{  // If the value of the photoresistor below 800, LED turns on.
    digitalWrite(LED, HIGH);  // HIGH means LED turning on lights.
    Serial.println("LED ON");  // Print "LED ON"
  }

  delay(100); // Delay for 1 milisecond.

}

// RESULT
// When photoresistor detect light brightness greater than 800 value LED will turning off.
// Whenhen photoresistor detect light brightness below than 800 value LED will turning on.
// This conceps suitable for automatic lights on when day become darker.