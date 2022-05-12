#pragma once

class ServoJoint{
  unsigned char _servoPin;
  unsigned char _middlePos;
  unsigned char _actualPos;
  unsigned char _maxPos;
  unsigned char _minPos;

  public:
    ServoJoint(unsigned char sPin, unsigned char midPos, unsigned char actPos, unsigned char maxPos, unsigned char minPos){_servoPin = sPin; _middlePos = midPos; _actualPos = actPos; _maxPos = maxPos; _minPos = minPos;}

      unsigned char getServoPin(){return _servoPin;}
      unsigned char getMidServoPos(){return _middlePos;}
      unsigned char getActServoPos(){return _actualPos;}
      unsigned char getMaxServoPos(){return _maxPos;}
      unsigned char getMinServoPos(){return _minPos;}

    void setActServoPos(unsigned char actualPos){_actualPos = actualPos;}
    ~ServoJoint();
};