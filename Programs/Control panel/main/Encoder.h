#pragma once

#include <Arduino.h>

#define SWITCH_PIN 3
#define ENCODER_R_PIN 4
#define ENCODER_L_PIN 5

class Encoder{
  bool _buttonState;
  char _encoderState;
  public:
    Encoder();
    void checkEncoder();

    bool getButtonState();
    int getEncoderState();
    ~Encoder();
};