// 9.2 WATER LEVEL TESTING SYSTEM
// 9.2 Function to determines whether the detected value exceeds the set threshold. If it does, the buzzer alarms.

#include <LiquidCrystal_I2C.h>  // Include the library for the I2C LCD.

#define BuzzerPin 16          // Define the pin for the buzzer as GPIO 16.
#define WaterLevelPin 33      // Define the pin for the water level sensor as GPIO 33.

// Create an LCD object with the I2C address 0x27 and a 16x2 character display.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);  // Initialize serial communication at a baud rate of 9600.
  pinMode(WaterLevelPin, INPUT);  // Set the water level pin as an input.

  lcd.init();  // Initialize the LCD.
  lcd.backlight();  // Turn on the LCD backlight.
  lcd.clear();  // Clear the LCD display.
}

void loop() {
  int ReadValue = analogRead(WaterLevelPin);  // Read the analog value from the water level sensor.
  
  lcd.setCursor(0, 0);  // Set the cursor to the first row, first column.
  lcd.print("WaterLevel:");  // Print "WaterLevel:" on the LCD.
  lcd.setCursor(6, 1);  // Set the cursor to the second row, seventh column.
  lcd.print(ReadValue);  // Print the read value on the LCD.

  // If the detected value exceeds the threshold (2000), the buzzer starts to alarm.
  if(ReadValue >= 2000) {
    tone(BuzzerPin, 659);  // Generate a tone at 659 Hz on the buzzer.
    delay(100);  // Wait for 100 milliseconds.
    tone(BuzzerPin, 532);  // Generate a tone at 532 Hz on the buzzer.
    delay(100);  // Wait for 100 milliseconds.
    tone(BuzzerPin, 659);  // Generate a tone at 659 Hz on the buzzer.
    delay(100);  // Wait for 100 milliseconds.
    noTone(BuzzerPin);  // Stop the buzzer.
  }

  delay(500);  // Wait for 500 milliseconds before the next loop iteration.
  lcd.clear();  // Clear the LCD display.
}

// RESULT
// LCD will displays the real-timme value of water level.
// When deteced value exceeds the threshold, the buzzer starts to alarm.
