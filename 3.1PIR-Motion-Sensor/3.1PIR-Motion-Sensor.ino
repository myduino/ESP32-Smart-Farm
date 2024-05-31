// 3.1 PIR MOTION SENSOR
// 3.1 Code purpose is to detects motion from presence of person by sensing the heat given off by the human.

// Make sure the pin number match with io23 you attach on the board.
#define PyroelectricPIN 23

// Set the setup here.
void setup() {

  Serial.begin(9600);  // Initialize serial communication and set baud rate to '9600'.

  pinMode(PIRmotion, INPUT);  // Set the PIR motion pin as input.

}

// The loop function runs repeatedly forever.
void loop() {
  
  int ReadValue = digitalRead(PIRmotion);  //Read the value of PIR motion sensor
  
  if(ReadValue){  // If PIR motion sensor get the value
    Serial.println("Someone");  // Print "Someone".
  }

  else{ // If 
    Serial.println("No one");  // Print "No one".
  }
  delay(100);
}