// 7.4 TEMPERATURE CONTROL SYSTEM
// 7.4 Function todetermines whether the detected values reach the set threshold.

#include <LiquidCrystal_I2C.h>  // Import the LiquidCrystal I2C library for the LCD display.
#include <Adafruit_Sensor.h>  // Import the Adafruit Unified Sensor library.
#include <DHT.h>  // Import the Adafruit DHT sensor library.

#define DHTPIN 17  // Define the DHT11 data pin as GPIO 17.
#define DHTTYPE DHT11  // Define the type of DHT sensor used.
#define MotorPin1 19  // Define MotorPin1 as GPIO pin 19 (IN+).
#define MotorPin2 18  // Define MotorPin2 as GPIO pin 18 (IN-).

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object with the specified pin and type.
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Create an LCD object with I2C address 0x27, 16 columns, and 2 rows.

// Set the setup here.
void setup() {
  lcd.init();  // Initialize the LCD.
  lcd.backlight();  // Turn on the LCD backlight.
  
  pinMode(MotorPin1, OUTPUT);  // Set MotorPin1 as an output pin.
  pinMode(MotorPin2, OUTPUT);  // Set MotorPin2 as an output pin.

  // Set PWM output to adjust the speed of the motor.
  ledcSetup(1, 1200, 8);  // Set frequency of LEDC Channel 1 to 1200 Hz, PWM resolution to 8 bits (duty cycle range 0-255).
  ledcAttachPin(MotorPin1, 1);  // Bind LEDC Channel 1 to the specified motor pin (GPIO 19) to output PWM signal.
  ledcSetup(3, 1200, 8);  // Set frequency of LEDC Channel 3 to 1200 Hz, PWM resolution to 8 bits (duty cycle range 0-255).
  ledcAttachPin(MotorPin2, 3);  // Bind LEDC Channel 3 to the specified motor pin (GPIO 18) to output PWM signal.

  dht.begin();  // Initialize the DHT sensor.
}

// Set the loop here.
void loop() {
  delay(2000);  // Wait for 2 seconds between measurements.

  // Read the temperature and humidity values from the DHT sensor.
  float humidity = dht.readHumidity();  // Read humidity value.
  float temperature = dht.readTemperature();  // Read temperature value in Celsius.

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display temperature and humidity on the LCD.
  lcd.setCursor(0, 0);  // Set the cursor to the first column of the first row.
  lcd.print("Temp:");  // Print "Temp:" on the LCD.
  lcd.setCursor(5, 0);  // Set the cursor to the sixth column of the first row.
  lcd.print(temperature);  // Print the temperature value.
  lcd.print("C");

  lcd.setCursor(0, 1);  // Set the cursor to the first column of the second row.
  lcd.print("Hum:");  // Print "Hum:" on the LCD.
  lcd.setCursor(5, 1);  // Set the cursor to the sixth column of the second row.
  lcd.print(humidity);  // Print the humidity value.
  lcd.print("%");

  // Control motor based on temperature.
  if (temperature >= 25) {
    // Turn left if the temperature is 25°C or higher.
    ledcWrite(1, 100);  // Set duty cycle of LEDC Channel 1 to 100 (out of 255), turning the motor left.
    ledcWrite(3, 0);  // Set duty cycle of LEDC Channel 3 to 0, stopping the second motor pin.
  } else {
    // Stop the motor if the temperature is below 25°C.
    delay(3000);  // Wait for 3 seconds.
    ledcWrite(1, 0);  // Set duty cycle of LEDC Channel 1 to 0, stopping the first motor pin.
    ledcWrite(3, 0);  // Set duty cycle of LEDC Channel 3 to 0, stopping the second motor pin.
    delay(200);  // Wait for 200 milliseconds.
  }
}

// RESULT
// LCD will display current humidity and temperature.
// When temperature reaches 29 Celcius, the fan will turn on to dissipate heat.