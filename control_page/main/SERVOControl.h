#pragma once

#include <Adafruit_PWMServoDriver.h>
#include "LittleFS.h"
#include "ServoJoint.h"
#include "ReadServo.h"
#include "Arduino.h"

#define SERVO_COUNT 16
#define SERVO_FREQ 50
#define SERVO_MID 90
#define SERVO_STEP 1

#define FILE_NAME "/servos_init.txt"

#define LOG(x) Serial.print(x)

class ServoControl{

  Adafruit_PWMServoDriver *_pwm;
  ServoJoint *_servo[SERVO_COUNT];
  //ReadServo* _rServo;
  File *_file;

  void initServos();
  int readFSUntil(char delimiter); 

  bool needMove = true;

  public:
    ServoControl();
      void printServosInfo();

      void moveServos(short period);
      void setEstimatedPositions(unch estimatedPositions[16]);

      bool getNeedMove(){return needMove;}
    ~ServoControl();
};