#pragma once

#include <PS2X_lib.h>

#define PS2_CLK 14
#define PS2_CMD 13
#define PS2_ATT 2
#define PS2_DATA 12

#define LOG(x) Serial.print(x)

class PS2_remote{
    PS2X *_ps2;

  public:
    PS2_remote();
      bool isPressed(int key);
      int readJoystick(int key);
    ~PS2_remote();
};