// 7.2 LCD 1602
// 7.2 LCD function to display values what have been set.

// Get the library from folder libraries.
#include <LiquidCrystal_I2C.h>  // Import the library for the LCD 1602.

// Initialize LCD 1602, 0x27 is I2C address.
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Initialize LCD.
  lcd.init();
  // Turn the (optional) backlight off/on.
  lcd.backlight();
  // lcd.noBacklight();

  // Set the position cursor.
  lcd.setCursor(0, 0);
  // LCD prints.
  lcd.print("HELLO WORLD 0");
  lcd.setCursor(0, 1);
  lcd.print("HELLO WORLD 1");

  // Clear displays.
  // lcd.clear();
}

void loop() {

  // Turn the display on/off (quickly).
  // lcd.noDisplay();
  // lcd.display();

  // Turns the underline cursor on/off
  // lcd.noCursor();
  // lcd.cursor();

  // Turn on and off the blinking cursor
  // lcd.noBlink();
  // lcd.blink();

  // These commands scroll the display without changing the RAM
  // lcd.scrollDisplayLeft();
  // lcd.scrollDisplayRight();

  // This is for text that flows Left to Right
  // lcd.leftToRight();
  // lcd.rightToLeft();

  // This will 'right justify' text from the cursor
  // lcd.autoscroll();
  // lcd.noAutoscroll();

}

// RESULT
// LCD WILL DISPLAY:
// "HELLO WORLD O".
// "HELLO WORLD 1".