// 10.2 AUTO IRRIGATION
// 10.2 Function to drives the water pump to irrigate via the relay module.

#include <LiquidCrystal_I2C.h>  // Import the LiquidCrystal_I2C library for LCD control.

#define BuzzerPin 16  // Define the pin for the buzzer as GPIO 16.
#define SoilHumidityPin 32  // Define the pin for the soil humidity sensor as GPIO 32.
#define WaterLevelPin 33  // Define the pin for the water level sensor as GPIO 33.
#define RelayPin 25  // Define the pin for the relay as GPIO 25.
#define ButtonPin 5  // Define the pin for the button as GPIO 5.
int value = 0;  // Initialize the button state variable.

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Create an LCD object with I2C address 0x27, 16 columns, and 2 rows.

void setup() {
  // Set the pins mode
  pinMode(BuzzerPin, OUTPUT);  // Set the buzzer pin as an output.
  pinMode(SoilHumidityPin, INPUT);  // Set the soil humidity sensor pin as an input.
  pinMode(WaterLevelPin, INPUT);  // Set the water level sensor pin as an input.
  pinMode(RelayPin, OUTPUT);  // Set the relay pin as an output.
  pinMode(ButtonPin, INPUT);  // Set the button pin as an input.

  // Initialize LCD
  lcd.init();  // Initialize the LCD.
  lcd.backlight();  // Turn on the LCD backlight.
  lcd.clear();  // Clear the LCD displays.
}

void loop() {
  // Define variables as the read values of water level, humidity, and button state
  int shvalue = analogRead(SoilHumidityPin);  // Read the soil humidity value.
  int wlvalue = analogRead(WaterLevelPin);  // Read the water level value.
  int ReadValue = digitalRead(ButtonPin);  // Read the button state.

  // Set the display position of cursor
  lcd.setCursor(0, 0);
  // Set the display position of character strings
  lcd.print("SoilHum:");
  lcd.setCursor(9, 0);
  lcd.print(shvalue);  // Display the soil humidity value.
  lcd.setCursor(0, 1);
  lcd.print("WaterLevel:");
  lcd.setCursor(11, 1);
  lcd.print(wlvalue);  // Display the water level value.

  // Determine whether the button is pressed
  if (ReadValue == 0) {
    // Eliminate the button shake
    delay(10);
    if (ReadValue == 0) {
      value = !value;  // Toggle the button state.
      Serial.print("The current status of the button is : ");
      Serial.println(value);  // Print the button state to the serial monitor.
    }
    // Again, determine whether the button is still pressed
    // Pressed: execute the loop; Released: exit the loop to next execution
    while (digitalRead(ButtonPin) == 0);
  }

  // When the detected humidity is lower than the set threshold, the buzzer starts to alarm. Press button to stop alarming.
  if (500 >= shvalue && value == 0) {
    tone(BuzzerPin, 532);
    delay(100);
    tone(BuzzerPin, 532);
    delay(100);
    tone(BuzzerPin, 659);
    delay(100);
    noTone(BuzzerPin);  // Stop alarming.
  }

  // When the detected water level is lower than the set threshold, the buzzer starts to alarm. Press button to stop alarming.
  if (500 >= wlvalue && value == 0) {
    tone(BuzzerPin, 411);
    delay(100);
    tone(BuzzerPin, 639);
    delay(100);
    tone(BuzzerPin, 411);
    delay(100);
    noTone(BuzzerPin);  // Stop alarming.
  }

  // When the detected humidity is lower than the set threshold, and the water is sufficient in the pool, irrigation starts automatically.
  if (500 >= shvalue && wlvalue >= 1000) {
    digitalWrite(RelayPin, HIGH);  // Turn on the relay.
    delay(400);  // Irrigation delay.
    digitalWrite(RelayPin, LOW);  // Turn off the relay.
    delay(700);  // Wait before the next operation.
  }

  delay(500);
  // Clear displays
  lcd.clear();  // Clear the LCD.
}

// RESULT
// If soil humidity value or water level above 500 DAC then buzzer will alarm.
// when the detected humidity is lower than the set threshold, it implies the soil is being arid and irrigation start automatically.
