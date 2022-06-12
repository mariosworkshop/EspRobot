#pragma once

#include <Adafruit_PWMServoDriver.h>
#include <FS.h>
#include "ServoJoint.h"

#define SERVOMIN  150
#define SERVOMAX  600
#define SERVO_COUNT 16
#define SERVO_FREQ 50
#define SERVO_MID 90

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

 // bool trebaPohnut = false;
  public:
    SERVOControl();
      void printServosInfo();

      void moveToPos(unch pin, unch pos, short period);
      void moveToPos(unch pin1, unch pin2, unch pos, short period);
      void moveToPos(unch pin1, unch pin2, unch pin3, unch pin4, unch pos, short period);

      short degreeToPulse(int degree);

     // void pohniServami(short period);
     // void setEstimatedPositions(unch estimatedPositions[12]);

    ~SERVOControl();
};