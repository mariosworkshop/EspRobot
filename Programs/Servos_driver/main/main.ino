#include "ServoControl.h"
#include "PS2_remote.h"
#include "Gyro.h"

ServoControl *driver;
PS2_remote *ps2;
Gyro *mpu;

unch positions[SERVO_COUNT] = {90, 130, 50, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 130, 50, 90};

void setup(){
  Serial.begin(115200);
  driver = new ServoControl();
  ps2 = new PS2_remote();
  mpu = new Gyro();

  driver->setEstimatedPositions(positions);
}

void loop(){
  driver->setEstimatedPositions(positions);
  mpu->readValues();
  if(!driver->getNeedMove()){
    if(Serial.available() > 0){
      parseSerial(',');
    }
    driver->setEstimatedPositions(positions);
  }
  driver->moveServos(30);
}

void parseSerial(char delimiter){
  String data = Serial.readString();
  LOG(data + "\n");

  String dataPart= "";
  int arrPos = 0;

  for(char sign : data){
    if(sign != delimiter){
      dataPart += sign;
    }
    else{
      positions[arrPos] = dataPart.toInt();
      LOG(String(arrPos) + " - " + String(positions[arrPos]) + "\n");
      dataPart = "";
      arrPos++;
    }
  }
}

void reactToPs2(){
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
  else if(ps2->isPressed(PSB_SQUARE)){
    positions[0] = 100;
    positions[4] = 95;
    positions[11] = 95;
    positions[15] = 100;
  }
  else if(ps2->isPressed(PSB_CIRCLE)){
    positions[0] = 80;
    positions[4] = 85;
    positions[11] = 85;
    positions[15] = 80;
  }
  else{}
}