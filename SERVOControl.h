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

class SERVOControl{

  Adafruit_PWMServoDriver *_pwm;
  ServoJoint *_servo[SERVO_COUNT];
  File *_file;
  public:
    SERVOControl();
      void initServos();
      void printServosInfo();

      void moveFourServos(unsigned char servoPins[4], short servosSteps[4]);
      void moveSingleServo(unsigned char pin, unsigned char pos);

      unsigned char tryFindServo(unsigned char pin);
      short degreeToPulse(int degree);
    ~SERVOControl();
};