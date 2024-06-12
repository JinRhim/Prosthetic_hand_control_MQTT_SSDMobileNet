//Display.cpp
#include "Display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


Display::Display(TwoWire *wire, uint8_t address) : display(SCREEN_WIDTH, SCREEN_HEIGHT, wire, OLED_RESET), address(address), wire(wire) {}

void Display::init() {
  if (this->wire == &Wire) {
    this->wire->setPins(21,22);
      if (! this->wire->begin(21, 22)) {
      Serial.println("error");
      };
  } else if (this->wire == &Wire1) {
    this->wire->setPins(33,32);
      if (! this->wire->begin(33, 32)) {
      Serial.println("error");
      };
  } else {
    Serial.println("wire.h failed");
  }

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
  
}

void Display::clear() {
  display.clearDisplay();
}

void Display::displayText(const String& text, uint8_t textSize) {
  display.clearDisplay();
  display.setTextSize(textSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}

void Display::drawBitMap(const uint8_t *bitmap) {
  display.clearDisplay();
  display.drawBitmap(0, 0, bitmap, 128, 64, WHITE);
  display.display();
}
