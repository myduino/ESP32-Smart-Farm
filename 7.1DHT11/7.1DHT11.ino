// 7.1 DHT11
// 7.1 Function is to reads the value of DHT11 temperature and humidity sensor.

// Get the the library from Adafruit.
#include <DHT.h>              // Import the library for the DHT sensor.
#include <Adafruit_Sensor.h>  // Import the Adafruit Unified Sensor library.

#define DHTPIN 17     // Set the DHT11 data pin to 17.
#define DHTTYPE DHT11 // Set the type of DHT sensor used.

DHT dht(DHTPIN, DHTTYPE); // Create a DHT object with the specified pin and type.

// Set the setup.
void setup() {
  Serial.begin(9600);                   // Initialize serial communication and set baud rate to 9600.
  Serial.println("DHT11 TEST PROGRAM"); // Print a message to the serial monitor.
  dht.begin();                          // Initialize the DHT sensor.
}

// The loop function run repeatedly forever.
void loop() {
  delay(2000);  // Wait for 2 seconds between measurements.

  float humidity = dht.readHumidity();       // Read humidity value.
  float temperature = dht.readTemperature(); // Read temperature value in Celsius.
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!"); // Print error message to the serial monitor.
    return;                                            // Exit the loop and try again.
  }

  float fahrenheit = Fahrenheit(temperature);                 // Convert temperature to Fahrenheit.
  float kelvin = Kelvin(temperature);                         // Convert temperature to Kelvin.
  float dew_point = dewPoint(temperature, humidity);          // Calculate the dew point.
  float dew_point_fast = dewPointFast(temperature, humidity); // Fast calculation of the dew point.

  // Display the readings.
  Serial.print("Humidity (%): ");     // Print the humidity label.
  Serial.println(humidity, 2);        // Print the humidity value with 2 decimal places.

  Serial.print("Temperature (°C): "); // Print the temperature label in Celsius.
  Serial.println(temperature, 2);     // Print the temperature value in Celsius with 2 decimal places.

  Serial.print("Temperature (°F): "); // Print the temperature label in Fahrenheit.
  Serial.println(fahrenheit, 2);      // Print the temperature value in Fahrenheit with 2 decimal places.

  Serial.print("Temperature (K): ");  // Print the temperature label in Kelvin.
  Serial.println(kelvin, 2);          // Print the temperature value in Kelvin with 2 decimal places.

  Serial.print("Dew Point (°C): ");   // Print the dew point label.
  Serial.println(dew_point);          // Print the dew point value.

  Serial.print("Dew Point Fast (°C): "); // Print the fast dew point label.
  Serial.println(dew_point_fast);        // Print the fast dew point value.
}

double Fahrenheit(double celsius) {
  return 1.8 * celsius + 32; // Convert Celsius to Fahrenheit.
}

double Kelvin(double celsius) {
  return celsius + 273.15; // Convert Celsius to Kelvin.
}

// Dew Point calculation. The air is saturated and dews are produced under this temperature.
// Reference: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double humidity) {
  double A0 = 373.15 / (273.15 + celsius); // Calculate intermediate value A0.
  double SUM = -7.90298 * (A0 - 1); // Calculate intermediate sum.
  SUM += 5.02808 * log10(A0); // Add to the sum.
  SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / A0))) - 1); // Add to the sum.
  SUM += 8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1))) - 1); // Add to the sum.
  SUM += log10(1013.246); // Add to the sum.
  double VP = pow(10, SUM - 3) * humidity; // Calculate vapor pressure.
  double T = log(VP / 0.61078); // Calculate intermediate temperature T.
  return (241.88 * T) / (17.558 - T); // Calculate and return the dew point in Celsius.
}

// Fast calculation of the Dew Point, its speed is 5 times faster than dewPoint().
// Reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity) {
  double a = 17.271; // Constant a.
  double b = 237.7; // Constant b.
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100); // Calculate intermediate temperature.
  double Td = (b * temp) / (a - temp); // Calculate and return the fast dew point in Celsius.
  return Td;
}

// RESULT
// After the code done compiled open serial monitor and it will show humidity and temperature level.
// Humidity will in percetage and temperature will in 3 unit measurement.