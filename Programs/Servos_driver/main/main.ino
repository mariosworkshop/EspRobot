//#include "SERVOControl.h"

/*
SERVOControl* control;

unsigned char positions[SERVO_COUNT] = {90, 115, 65, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 115, 65, 90};
*/

void setup(){
  Serial.begin(115200);
  //control = new SERVOControl();
  //control->setEstimatedPositions(unch estimatedPositions[12]);
}

void loop(){
  /*
  if(!control->getNeedMove()){
    if(Serial.available() > 0){
      parseSerial(',');
    }
    control->setEstimatedPositions(positions);
  }
  control->moveServos(100);
  */
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