#pragma once

#include "ESERVO.h"
#include <Adafruit_PWMServoDriver.h>
#include <FS.h>

#define SERVO_COUNT 10
#define SERVO_DELAY 30
#define POS_FILENAME "/servo_pos.txt"

class ESERVODRIVER{
  private:

    ESERVO *_servos[SERVO_COUNT];
    Adafruit_PWMServoDriver *_driver;

  public:
    ESERVODRIVER();

    void initializeServos();
    void printServos();
    void setServoPos(short servoPin, short pos);
    void moveTwoServoTo(short servoPin1, short servoPin2, short step1, short step2);
    void moveFourServoTo(short servoPin1, short servoPin2, short servoPin3, short servoPin4, short step1, short step2, short step3, short step4);

    short tryFindServo(short &pin);

    ~ESERVODRIVER();
};
