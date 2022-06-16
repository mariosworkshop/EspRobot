#include "SERVOControl.h"

SERVOControl* control;

unsigned char positions[16] = {100, 90, 90, 90, 100, 90, 90, 90, 90, 90, 90, 100, 90, 90, 90, 100};

void setup(){
  Serial.begin(115200);
  control = new SERVOControl();
  //control->setEstimatedPositions(unch estimatedPositions[12]);
}

void loop(){
  if(!control->getNeedMove()){
    control->setEstimatedPositions(positions);
  }
  control->moveServos(100);
}