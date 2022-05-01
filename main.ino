#include "ESERVODRIVER.h"
#include <Adafruit_MPU6050.h>

ESERVODRIVER* eDriver;

Adafruit_MPU6050 mpu;

// == 4  == 11
// || 3  || 12
// || 2  || 13
// || 1  || 14
// == 0  == 15

void setup() {
  Serial.begin(115200);
  eDriver = new ESERVODRIVER();
  initializeGyro();
}

void loop() {
  /*sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  delay(500); */ 
  firstMove();
  walk();
}

void firstMove(){
  eDriver->moveFourServoTo(4, 11, 0, 15, 20, 20, 40, 40);
}

void walk(){
  eDriver->moveTwoServoTo(12, 13, -30, 30);
  eDriver->moveTwoServoTo(0, 15, 0, -20);
  eDriver->moveTwoServoTo(3, 2, -30, 30);
  eDriver->moveFourServoTo(0, 15, 4, 11, -70, -60, -40, -40);
  eDriver->moveTwoServoTo(12, 13, 30, -30);
  eDriver->moveTwoServoTo(3, 2, 60, -60);
  eDriver->moveFourServoTo(0, 15, 4, 11, 70, 80, 40, 40);
  eDriver->moveTwoServoTo(3, 2, -30, 30);
}

void pickRightLegUp(){
  if(Serial.available() > 0){
    String data = Serial.readString();
    String pin = "";
    String pos = "";
    for(int i = 0; i < data.length(); i++){
      if(data[i] == ','){
        pin = data.substring(0, i);
        pos = data.substring(i+1, data.length());
        break;
      }
    }
    Serial.println("Pin serva: " + pin + "\n" + "Pozicia serva: " + pos);
    eDriver->setServoPos(pin.toInt(), pos.toInt());
  }
}
void initializeGyro(){
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}