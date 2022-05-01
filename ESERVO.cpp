#include "ESERVO.h"

ESERVO::ESERVO(short pin, short minPos, short maxPos, short defaultPos){
  _minPosition = minPos;
  _maxPosition = maxPos;
  _defaultPosition = defaultPos;
  _pin = pin;
  setActualPos(_defaultPosition);
}

ESERVO::~ESERVO(){

}
