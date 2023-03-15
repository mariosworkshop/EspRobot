#pragma once

#include "Arduino.h"

#define unint unsigned int
#define CONTROL_PINS 5

class ReadServo{
  unint controlPins[CONTROL_PINS]; 

  public:
    ReadServo(unint s0, unint s1, unint s2, unint s3, unint r0);
      int readValue(int channel);
    ~ReadServo();
};