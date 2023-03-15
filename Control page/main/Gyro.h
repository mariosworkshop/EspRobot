#pragma once 

#include <Adafruit_MPU6050.h>

#define LOG(x) Serial.print(x)

class Gyro{
    Adafruit_MPU6050 *_mpu;
    sensors_event_t acc, gyr, temp;

    void setGyroRanges();

  public:
    Gyro();
    Gyro(int address);
      void readValues();
    ~Gyro();
};