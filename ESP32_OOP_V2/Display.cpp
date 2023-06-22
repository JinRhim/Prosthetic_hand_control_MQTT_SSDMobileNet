//Display.cpp
#include "Display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

Display::Display(uint8_t address) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), address(address) {}

void Display::init(uint8_t address) {
  if (!display.begin(SSD1306_SWITCHCAPVCC, this->address)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {} // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  delay(200);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Display");
  display.println("Setup");
  display.println("Complete"); 
  display.display();
  delay(500);
  
}

void Display::clear() {
  display.clearDisplay();
}

void Display::displayText(const String& text, uint8_t textSize) {
  display.setTextSize(textSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}
