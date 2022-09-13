#include "SERVOControl.h"
#include <Adafruit_MPU6050.h>

SERVOControl *control;
Adafruit_MPU6050 mpu;

unch positions[SERVO_COUNT] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
char ax = 0;

void setup(){
  Serial.begin(115200);
  control = new SERVOControl();
  control->setEstimatedPositions(positions);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.print("Acceleration X: ");
  Serial.println(a.acceleration.x);

  if(!control->getNeedMove()){
    if(Serial.available() > 0){
      parseSerial(',');
    }
    control->setEstimatedPositions(positions);
  }
  control->moveServos(30);

  if (ax != a.acceleration.x){ //naklananie noh
    ax = map(ax, -10, 10, 180, 0);
    positions[14] = ax;
    positions[1] = map(ax, 180, 0, 0, 180);
    control->setEstimatedPositions(positions);
  }
  ax = a.acceleration.x;
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
