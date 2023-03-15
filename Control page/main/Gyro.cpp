#include "Gyro.h"

Gyro::Gyro(){
  _mpu = new Adafruit_MPU6050();
  if (!_mpu->begin()){
    LOG("\nFailed to find MPU6050 chip");
  }
  LOG("\nMPU6050 chip found\n");
  setGyroRanges();
}

Gyro::Gyro(int addr){
  if (!_mpu->begin(addr)) {
    LOG("\nFailed to find MPU6050 chip, try another address");
    while (1) {
      delay(10);
    }
  }
  LOG("\nMPU6050 chip found");
  setGyroRanges();
}

void Gyro::setGyroRanges(){
  _mpu->setAccelerometerRange(MPU6050_RANGE_8_G);
  _mpu->setGyroRange(MPU6050_RANGE_500_DEG);
  _mpu->setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void Gyro::readValues(){
  _mpu->getEvent(&acc, &gyr, &temp);
}

Gyro::~Gyro(){
}