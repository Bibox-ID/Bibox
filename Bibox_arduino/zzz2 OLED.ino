#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                
  display.begin();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,5);
  display.println("Bibox"); 
  display.display();
  delay(2000);
  display.invertDisplay(false);
  delay(2000); 
  display.invertDisplay(true);
  delay(2000); 
  display.invertDisplay(false); 
  display.clearDisplay();
}

void loop() {
}