#include "SERVOControl.h"

SERVOControl *control;

void setup(){
  Serial.begin(115200);

  control->moveSingleServo(0, control->tryFindServo(0)->getActServoPos() + 10);
  control->moveSingleServo(15, control->tryFindServo(15)->getActServoPos() + 10);
}

void loop(){
}