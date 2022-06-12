#pragma once

#include <Adafruit_PWMServoDriver.h>
#include <FS.h>
#include "ServoJoint.h"

#define SERVOMIN  150
#define SERVOMAX  600
#define SERVO_COUNT 16
#define SERVO_FREQ 50

#define FILE_NAME "/servos_init.txt"

#define READ_NUM() _file->readStringUntil(' ').toInt()
#define unch unsigned char


class SERVOControl{

  Adafruit_PWMServoDriver *_pwm;
  ServoJoint *_servo[SERVO_COUNT];
  File *_file;
  public:
    SERVOControl();
      void initServos();
      void printServosInfo();

      void moveToPos(unch pin, unch pos, short period);
      void moveToPos(unch pin1, unch pin2, unch pos, short period);
      void moveToPos(unch pin1, unch pin2, unch pin3, unch pin4, unch pos, short period);

      ServoJoint* tryFindServo(unch pin);
      short degreeToPulse(int degree);
    ~SERVOControl();
};