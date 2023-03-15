#pragma once

#define unch unsigned char

#define SERVOMIN  150
#define SERVOMAX  600

class ServoJoint{
  unch _step, _estimatedPos, _servoPin, _middlePos, _actualPos, _maxPos, _minPos;

  public:
    ServoJoint(unch sPin, unch midPos, unch actPos, unch maxPos, unch minPos, int step){
      _servoPin = sPin; 
      _middlePos = midPos; 
      _actualPos = actPos; 
      _maxPos = maxPos; 
      _minPos = minPos;
      _estimatedPos = _middlePos, 
      _step = step;
    }

    unch getServoPin(){return _servoPin;}
    unch getMidServoPos(){return _middlePos;}
    unch getActServoPos(){return _actualPos;}
    unch getMaxServoPos(){return _maxPos;}
    unch getMinServoPos(){return _minPos;}
    unch getEstimatedPosition(){return _estimatedPos;}

    bool makeStep(Adafruit_PWMServoDriver *_pwm) {
      if (_estimatedPos == _actualPos) return false;
        if (abs(_actualPos - _estimatedPos) < _step) {
          _pwm->setPWM(_servoPin, 0, degreeToPulse(_estimatedPos));
          _actualPos = _estimatedPos;
          return true;
        }
        if (_actualPos > _estimatedPos) {
          _pwm->setPWM(_servoPin, 0, degreeToPulse(_actualPos - _step));
          _actualPos -= _step;
        } else {
          _pwm->setPWM(_servoPin, 0, degreeToPulse(_actualPos + _step)); 
          _actualPos += _step;
        }
          return true;
    }

    short degreeToPulse(int degree){
      return map(degree, 0, 180, SERVOMIN, SERVOMAX);
    }

    void setEstimatedPosition(unch estimated) {_estimatedPos = estimated;};
    void setActServoPos(unch actualPos){_actualPos = actualPos;}
    
    ~ServoJoint();
};