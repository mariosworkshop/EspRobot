#pragma once

#include <Adafruit_PWMServoDriver.h>
#include "LittleFS.h"
#include "ServoJoint.h"

#define SERVO_COUNT 16
#define SERVO_FREQ 50
#define SERVO_MID 90
#define SERVO_STEP 1

#define FILE_NAME "/servos_init.txt"

#define unch unsigned char


class SERVOControl{

  Adafruit_PWMServoDriver *_pwm;
  ServoJoint *_servo[SERVO_COUNT];
  File *_file;

  void initServos();
  int readFSUntil(char delimiter); 
  ServoJoint* tryFindServo(unch pin);
  ServoJoint* tryFindBiggActServo(ServoJoint* servo[4]); //najdi najvacsiu aktualnu poziciu

  bool needMove = true;

  public:
    SERVOControl();
      void printServosInfo();

      void moveServos(short period);
      void setEstimatedPositions(unch estimatedPositions[16]);

      bool getNeedMove(){return needMove;}
    ~SERVOControl();
};