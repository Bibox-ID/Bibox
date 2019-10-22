//oled 12c SDA ke D2 & SCL ke D1 

#include <ESP_SSD1306.h>    
#include <Adafruit_GFX.h>   
#include <SPI.h>           
#include <Wire.h>          
#define OLED_RESET  16  
ESP_SSD1306 display(OLED_RESET);

void setup(){
  display.begin();  // Switch OLED
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,10);
  display.println("Bibox");
  display.setCursor(20,40);
  display.println(" IoT ");
  display.display();
}
  
void loop() {
}