//Display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



class Display {
public:
  Display(uint8_t address);
  void init();
  void clear();
  void displayText(const String& text, uint8_t textSize);
private:
  Adafruit_SSD1306 display;
  const uint8_t address; 
};

#endif
