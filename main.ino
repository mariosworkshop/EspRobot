#include "SERVOControl.h"

SERVOControl *control;

void setup(){
  Serial.begin(115200);
  control = new SERVOControl();
  control->moveSingleServo(0, 100); 
  control->moveSingleServo(15, 98);
  control->moveSingleServo(4, 102); 
  control->moveSingleServo(11, 104);
}

void loop(){
  
}