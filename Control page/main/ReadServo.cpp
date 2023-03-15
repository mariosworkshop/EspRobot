#include "ReadServo.h"

ReadServo::ReadServo(unint s0, unint s1, unint s2, unint s3, unint r0){
  unint cPins[] = {s0, s1, s2, s3, r0};
  for (unint i = 0; i < CONTROL_PINS; i++){
    controlPins[i] = cPins[i];
  }

  for (unint i = 0; i < CONTROL_PINS - 1; i++){
    pinMode(controlPins[i], OUTPUT);
    digitalWrite(controlPins[i], LOW);
  }
}

int ReadServo::readValue(int channel){
  int mltplxerChannel[16][4]{
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 0, 1, 1},
    {0, 1, 1, 1},
    {1, 1, 1, 1}
  };

  for (int i = 0; i < CONTROL_PINS - 1; i++){
    digitalWrite(controlPins[i], mltplxerChannel[channel][i]);
  }

  return map(analogRead(controlPins[CONTROL_PINS - 1]), 0, 1023, 0, 180);
}

ReadServo::~ReadServo(){
}