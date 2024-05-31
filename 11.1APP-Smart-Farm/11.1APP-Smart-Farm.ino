// 11.1 APP SMART FARM
// 11.1 This is last step in this project ESP32 Smart Farm Kit. Which is to combine all module function to integrate in one app.

#include <SD.h>               // Include the SD library
#include <sd_defines.h>       // Include SD defines
#include <sd_diskio.h>        // Include SD disk I/O
#include <Arduino.h>          // Include the Arduino library
#ifdef ESP32
#include <WiFi.h>             // Include the WiFi library for ESP32
#elif defined(ESP8266)
#include <ESP8266WiFi.h>      // Include the WiFi library for ESP8266
#endif
#include <DHT11.h>            // Include the DHT11 sensor library
#include <ESP32_Servo.h>      // Include the Servo library for ESP32
#include <LiquidCrystal_I2C.h>// Include the LCD I2C library
#include "BuzzerMusic.h"      // Include the Buzzer Music library

// Pin definitions for sensors and actuators
#define DHT11PIN 17           // Pin for the DHT11 temperature and humidity sensor
#define RAINWATERPIN 35       // Pin for the rainwater sensor
#define LIGHTPIN 34           // Pin for the light sensor (photoresistor)
#define WATERLEVELPIN 33      // Pin for the water level sensor
#define SOILHUMIDITYPIN 32    // Pin for the soil humidity sensor
#define LEDPIN 27             // Pin for the LED
#define RELAYPIN 25           // Pin for the relay (to control water pump)
#define SERVOPIN 26           // Pin for the servo motor
#define FANPIN1 19            // Pin for the fan IN+ 
#define FANPIN2 18            // Pin for the fan IN-
#define BUZZERPIN 16          // Pin for the buzzer
#define ButtonPin 5           // Pin for the button

// WiFi credentials
const char* ssid = "myinvententerprise"; 
const char* pwd = "04222682"; 

// Initialize LCD1602 with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2); 
WiFiServer server(80);  // Initialize WiFi server on port 80
DHT11 dht11(DHT11PIN);  // Initialize DHT11 sensor on defined pin
Servo myservo;          // Create servo object to control a servo motor

// Variables for storing sensor data and client requests
String request; 
String dataBuffer; 
int Temperature;   // Variable for temperature
int Humidity;      // Variable for humidity
int SoilHumidity;  // Variable for soil humidity
int Light;         // Variable for light intensity
int WaterLevel;    // Variable for water level
int Rainwater;     // Variable for rainwater
int result;        // Variable for result from DHT11 sensor reading
int value = 0;     // Initial button value

void setup() { 
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  WiFi.begin(ssid, pwd);  // Connect to WiFi network
  Serial.println("Connecting to WiFi..."); 
  while (WiFi.status() != WL_CONNECTED) {  // Wait until connected to WiFi
    delay(1000); 
    Serial.print("."); 
  } 
  delay(1000); 
  Serial.println("Connected to WiFi"); 
  Serial.print("WiFi NAME:"); 
  Serial.println(ssid); 
  Serial.print("IP:"); 
  Serial.println(WiFi.localIP()); 

  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the LCD backlight
  lcd.clear();  // Clear the LCD display
  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("IP:");  // Print "IP:" on the LCD
  lcd.setCursor(0, 1);  // Set cursor to the second row
  lcd.print(WiFi.localIP());  // Print the IP address on the LCD

  // Set pin modes for sensors and actuators
  pinMode(LEDPIN, OUTPUT); 
  pinMode(RAINWATERPIN, INPUT); 
  pinMode(LIGHTPIN, INPUT); 
  pinMode(SOILHUMIDITYPIN, INPUT); 
  pinMode(WATERLEVELPIN, INPUT); 
  pinMode(RELAYPIN, OUTPUT); 
  pinMode(FANPIN1, OUTPUT); 
  pinMode(FANPIN2, OUTPUT); 
  pinMode(BUZZERPIN, OUTPUT); 
  pinMode(ButtonPin, INPUT);
  delay(1000); 

  myservo.attach(SERVOPIN);  // Attach the servo motor to the servo pin
  server.begin();  // Start the WiFi server
} 

void loop() { 
  WiFiClient client = server.available();  // Check if a client is connected to the server
  if (client) {  // If a client is connected
    Serial.println("New client connected"); 
    while (client.connected()) {  // While the client is connected
      if (client.available()) {  // If the client sends data
        request = client.readStringUntil('s');  // Read the client request
        Serial.print("Received message: "); 
        Serial.println(request); 
      } 
      getSensorsData();  // Get sensor data
      dataBuffer = "";  // Clear the data buffer
      dataBuffer += String(Temperature, HEX);  // Add temperature data to buffer in hexadecimal
      dataBuffer += String(Humidity, HEX);  // Add humidity data to buffer in hexadecimal
      dataBuffer += dataHandle(SoilHumidity);  // Add soil humidity data to buffer
      dataBuffer += dataHandle(Light);  // Add light data to buffer
      dataBuffer += dataHandle(WaterLevel);  // Add water level data to buffer
      dataBuffer += dataHandle(Rainwater);  // Add rainwater data to buffer
      client.print(dataBuffer);  // Send data buffer to client
      delay(500); 

      // Handle client requests
      if (request == "a") { 
        digitalWrite(LEDPIN, HIGH);  // Turn on the LED
      } else if (request == "A") { 
        digitalWrite(LEDPIN, LOW);  // Turn off the LED
      } else if (request == "b") { 
        digitalWrite(RELAYPIN, HIGH);  // Turn on the relay (start irrigation)
        delay(400);  
        digitalWrite(RELAYPIN, LOW); 
        delay(650); 
      } else if (request == "c") { 
        delay(800); 
        digitalWrite(FANPIN1, HIGH);  // Turn on the fan
        digitalWrite(FANPIN2, LOW); 
        delay(200); 
      } else if (request == "C") { 
        digitalWrite(FANPIN1, LOW);  // Turn off the fan
        digitalWrite(FANPIN2, LOW); 
      } else if (request == "d") { 
        myservo.write(80);  // Open feeding box
        delay(500); 
      } else if (request == "D") { 
        myservo.write(180);  // Close feeding box
      } else if (request == "e") { 
        Music();  // Play music
      } 
      request = "";  // Clear the request
    } 
    Serial.println("Client disconnected"); 
  } 

  int shvalue = analogRead(SOILHUMIDITYPIN);  // Read soil humidity value
  int wlvalue = analogRead(WATERLEVELPIN);  // Read water level value
  int ReadValue = digitalRead(ButtonPin);  // Read button state

  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("SoilHum:");  // Print "SoilHum:" on the LCD
  lcd.setCursor(9, 0);  // Set cursor position
  lcd.print(shvalue);  // Print soil humidity value
  lcd.setCursor(0, 1);  // Set cursor to the second row
  lcd.print("WaterLevel:");  // Print "WaterLevel:" on the LCD
  lcd.setCursor(11, 1);  // Set cursor position
  lcd.print(wlvalue);  // Print water level value

  if (ReadValue == 0) {  // If button is pressed
    delay(10);  // Debounce delay
    if (ReadValue == 0) { 
      value = !value;  // Toggle value
      Serial.print("The current status of the button is : ");
      Serial.println(value);
    }
    while (digitalRead(ButtonPin) == 0);  // Wait for button release
  }

  if (500 >= shvalue && value == 0) {  // If soil humidity is below threshold and button is not pressed
    tone(BUZZERPIN, 532);  // Sound the buzzer
    delay(100);
    tone(BUZZERPIN, 532);
    delay(100);
    tone(BUZZERPIN, 659);
    delay(100);
    noTone(BUZZERPIN);  // Stop the buzzer
  }

  if (500 >= wlvalue && value == 0) {  // If water level is below threshold and button is not pressed
    tone(BUZZERPIN, 411);  // Sound the buzzer
    delay(100);
    tone(BUZZERPIN, 639);
    delay(100);
    tone(BUZZERPIN, 411);
    delay(100);
    noTone(BUZZERPIN);  // Stop the buzzer
  }

  if (500 >= shvalue && wlvalue >= 1000) {  // If soil humidity is below threshold and water level is above threshold
    digitalWrite(RELAYPIN, HIGH);  // Turn on the relay (start irrigation)
    delay(400);
    digitalWrite(RELAYPIN, LOW); 
    delay(700);
  }
  delay(500);
  lcd.clear();  // Clear the LCD display
} 

void getSensorsData() { 
  result = dht11.readTemperatureHumidity(Temperature, Humidity);  // Read temperature and humidity from DHT11 sensor
  Rainwater = analogRead(RAINWATERPIN);  // Read rainwater sensor value
  Light = analogRead(LIGHTPIN);  // Read light sensor value
  SoilHumidity = analogRead(SOILHUMIDITYPIN) * 2.3;  // Read and scale soil humidity value
  WaterLevel = analogRead(WATERLEVELPIN) * 2.5;  // Read and scale water level value
} 

void Music() { 
  for (int thisNote = 0; thisNote < 98; thisNote++) {  // Loop through the melody notes
    int noteDuration = 700 / noteDurations2[thisNote];  // Calculate note duration
    tone(BUZZERPIN, melody2[thisNote], noteDuration);  // Play the note
    int pauseBetweenNotes = noteDuration * 1.30;  // Calculate pause duration
    delay(pauseBetweenNotes);  // Pause between notes
    noTone(BUZZERPIN);  // Stop the buzzer
  } 
} 

String dataHandle(int data) { 
  int percentage = (data / 4095.0) * 100;  // Convert sensor data to percentage
  percentage = percentage > 100 ? 100 : percentage;  // Ensure percentage is within 0-100%
  char hexString[3]; 
  sprintf(hexString, "%02X", percentage);  // Convert percentage to hexadecimal string
  return hexString;  // Return hexadecimal string
} 

// NOTE
// You need to download app name "IOT Farm" from GoogleStore/AppStore.
// Make sure you have done testing all functionality each module before.
//
// RESULT
// After you run whole codes LCD will display IP address, type the same IP address at IOT Farm app t o get in the same local network.
// Once you done the app will display real-time value in the app for each sensor in percentage.
// There are also button for you locally remote all the component function there.
