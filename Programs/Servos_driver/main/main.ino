#include "SERVOControl.h"
#include "PS2_remote.h"
#include "Gyro.h"

SERVOControl *control;
PS2_remote *ps2;
Gyro *mpu;

unch positions[SERVO_COUNT] = {90, 130, 50, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 130, 50, 90};

void setup(){
  Serial.begin(115200);
  control = new SERVOControl();
  ps2 = new PS2_remote();
  mpu = new Gyro();

  control->setEstimatedPositions(positions);
}

void loop(){
  if(ps2->isPressed(PSB_TRIANGLE)){
    positions[1] = 90;
    positions[2] = 90;
    positions[13] = 90;
    positions[14] = 90;
  }
  else if(ps2->isPressed(PSB_CROSS)){
    positions[1] = 130;
    positions[2] = 50;
    positions[13] = 130;
    positions[14] = 50;
  }
  else{}
  control->setEstimatedPositions(positions);
  mpu->readValues();
  if(!control->getNeedMove()){
    if(Serial.available() > 0){
      parseSerial(',');
    }
    control->setEstimatedPositions(positions);
  }
  control->moveServos(30);
}

void parseSerial(char delimiter){
  String data = Serial.readString();
  Serial.println(data);
  String dataPart= "";
  int arrPos = 0;
  for(char sign : data){
    if(sign != delimiter){
      dataPart += sign;
    }
    else{
      positions[arrPos] = dataPart.toInt();
      Serial.println(String(arrPos) + " - " + String(positions[arrPos]));
      dataPart = "";
      arrPos++;
    }
  }
}