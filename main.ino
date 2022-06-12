#include "SERVOControl.h"

SERVOControl* control;

void setup(){
  Serial.begin(115200);
  control = new SERVOControl();
  //control->moveToPos(0, control->tryFindServo(0)->getActServoPos() + 10, 100);
  //control->moveToPos(15, control->tryFindServo(15)->getActServoPos() + 10, 100);
  //control->moveToPos(4, 11, 100, 70);
  //control->moveToPos(0, 15, 100, 70);
  control->moveToPos(0, 15, 4, 11, 100, 100);
}

void loop(){
}