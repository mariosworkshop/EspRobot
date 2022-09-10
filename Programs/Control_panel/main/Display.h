#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Bitmaps.h"
#include "Encoder.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define OLED_RESET -1

#define SCREEN_ADDRESS 0x3C

#define LOG(x) Serial.println(x)

class Display{
  Adafruit_SSD1306 *oled;
  Encoder *encoder;
  
  void initDisplay();
  void controlScreen();

  public:
    Display();
    ~Display();
};