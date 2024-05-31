// 8.2 SOIL HUMIDITY TESTING SYSTEM
// 8.2 Function to determines whether the read value exceeds the set threshold. If it does, the buzzer alarms.

// Import the library for controlling the LCD display.
#include <LiquidCrystal_I2C.h>

#define BuzzerPin 16  // Define the pin for the buzzer as GPIO 16.
#define SoilHumidityPin 32  // Define the pin for the soil humidity sensor as GPIO 32.

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Create an LCD object with I2C address 0x27 and 16x2 size.

void setup() {
  pinMode(BuzzerPin, OUTPUT);  // Set the buzzer pin as an output.
  pinMode(SoilHumidityPin, INPUT);  // Set the soil humidity pin as an input.

  lcd.init();  // Initialize the LCD.
  lcd.backlight();  // Turn on the backlight for the LCD.
  lcd.clear();  // Clear the LCD display.
}

void loop() {
  float shvalue = analogRead(SoilHumidityPin);  // Read the analog value from the soil humidity sensor.

  lcd.setCursor(0, 0);  // Set the cursor to the first column of the first row.
  lcd.print("SoilHum:");  // Print "SoilHum:" to the LCD.
  lcd.setCursor(9, 0);  // Set the cursor to the tenth column of the first row.
  lcd.print(shvalue);  // Print the soil humidity value to the LCD.

  // If the detected value is lower than the set threshold, the buzzer emits sound.
  if (shvalue <= 200) {  // Check if the soil humidity value is less than or equal to 200.
    tone(BuzzerPin, 532);  // Emit a 532 Hz sound from the buzzer.
    delay(100);  // Wait for 100 milliseconds.
    tone(BuzzerPin, 532);  // Emit a 532 Hz sound from the buzzer again.
    delay(100);  // Wait for 100 milliseconds.
    tone(BuzzerPin, 659);  // Emit a 659 Hz sound from the buzzer.
    delay(100);  // Wait for 100 milliseconds.
    noTone(BuzzerPin);  // Stop the buzzer from emitting sound.
  }
  
  delay(500);  // Wait for 500 milliseconds before the next reading.
  lcd.clear();  // Clear the LCD display.
}

// RESULT
// When sensor detected soil humidity value greater than 200 the buzzer will alarmed.
// If the value below than 200 then nothing will happened.