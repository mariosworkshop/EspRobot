#pragma once

#define unch unch

class ServoJoint{
  unch _servoPin;
  unch _middlePos;
  unch _actualPos;
  unch _maxPos;
  unch _minPos;

  public:
    ServoJoint(unch sPin, unch midPos, unch actPos, unch maxPos, unch minPos){_servoPin = sPin; _middlePos = midPos; _actualPos = actPos; _maxPos = maxPos; _minPos = minPos;}

      unch getServoPin(){return _servoPin;}
      unch getMidServoPos(){return _middlePos;}
      unch getActServoPos(){return _actualPos;}
      unch getMaxServoPos(){return _maxPos;}
      unch getMinServoPos(){return _minPos;}

    void setActServoPos(unch actualPos){_actualPos = actualPos;}
    ~ServoJoint();
};