#pragma once

#define unch unsigned char

class ServoJoint{
 // int _step; // toto 
  //int _pin;
  //unch _estimatedPosition; // toto
  unch _servoPin;
  unch _middlePos;
  unch _actualPos;
  unch _maxPos;
  unch _minPos;

  public:
    ServoJoint(unch sPin, unch midPos, unch actPos, unch maxPos, unch minPos/*, int step, int pin*/){_servoPin = sPin; _middlePos = midPos; _actualPos = actPos; _maxPos = maxPos; _minPos = minPos;/*_estimatedPosition = _middlePos, _step = ste, _pin = pin*/}

      unch getServoPin(){return _servoPin;}
      unch getMidServoPos(){return _middlePos;}
      unch getActServoPos(){return _actualPos;}
      unch getMaxServoPos(){return _maxPos;}
      unch getMinServoPos(){return _minPos;}



      /*bool makeStep(Adafruit_PWMServoDriver * _pwm) {
              if (estimatedPosition == _actualPosition) return false;
          if (abs(_actualPosition - _estimatedPosition) < _step) {
              _pwm->setPWM(_pin, _estimatedPosition, degreeToPulse(i)); // toto neviem ako mam nastavit
              _actualPosition -= _estimatedPosition;
              return true;
          }
          if (_actualPos > estimatedPosition) {
              _pwm->setPWM(_pin, _actualPosition - _step, degreeToPulse(i));// ani toto
              _actualPosition -= _step;
          } else {
              _pwm->setPWM(_pin, _actualPosition + _step, degreeToPulse(i));  // ani toto  
              _actualPosition += _step;
          }
          return true;

      }; // toto
      void setEstimatedPosition(unch estimated) {_estimatedPosition = estimated;}; // toto

*/

      void setActServoPos(unch actualPos){_actualPos = actualPos;}
      bool isAtCorner(unch pos){ if(pos == _maxPos || pos == _minPos){ return true; } return false; }
    ~ServoJoint();
};