#include "ESERVODRIVER.h"

ESERVODRIVER::ESERVODRIVER(){
  _driver = new Adafruit_PWMServoDriver(0x40);
  _driver->begin();
  _driver->setOscillatorFrequency(27000000);
  _driver->setPWMFreq(50);
  delay(10);
  SPIFFS.begin();
  initializeServos();
  printServos();
}
void ESERVODRIVER::initializeServos(){
  File _file = SPIFFS.open(POS_FILENAME, "r");

  for (int i = 0; i < SERVO_COUNT; i++){
    _servos[i] = new ESERVO(_file.readStringUntil('\n').toInt(), _file.readStringUntil('\n').toInt(), _file.readStringUntil('\n').toInt(), _file.readStringUntil('\n').toInt());
    setServoPos(_servos[i]->getPin(), _servos[i]->getDefaultPos());
  }
  _file.close();
}
void ESERVODRIVER::printServos(){
  for (int i = 0; i < SERVO_COUNT; i++){
    Serial.println("Pin serva: " + String(_servos[i]->getPin()));
    Serial.println("Min serva: " + String(_servos[i]->getMinPos()));
    Serial.println("Max serva: " + String(_servos[i]->getMaxPos()));
    Serial.println("Aktuálna serva: " + String(_servos[i]->getActualPos()));
    delay(50);
  }
}
void ESERVODRIVER::setServoPos(short servoPin, short pos){
  short arrayPos = tryFindServo(servoPin);
  if (arrayPos == -1){ return;}
  //if (_servos[arrayPos]->getMaxPos() < pos || _servos[arrayPos]->getMinPos() > pos){return;}
  if (_servos[arrayPos]->getActualPos() < pos){
    for (int i = _servos[arrayPos]->getActualPos(); i <= pos; i++){
      _driver->setPWM(_servos[arrayPos]->getPin(), 0, i);
      delay(SERVO_DELAY);
    }
  }
  else{
    for (int i = _servos[arrayPos]->getActualPos(); i >= pos; i--){
      _driver->setPWM(_servos[arrayPos]->getPin(), 0, i);
      delay(SERVO_DELAY);
    }
  }
  _servos[arrayPos]->setActualPos(pos);
}

void ESERVODRIVER::moveTwoServoTo(short servoPin1, short servoPin2, short step1, short step2){
  short arrayPos1 = tryFindServo(servoPin1);
  short arrayPos2 = tryFindServo(servoPin2);
  short bgStep = max(abs(step1), abs(step2));

  for(int i = 1; i <= bgStep; i++){
    if (i <= abs(step1)){
      _driver->setPWM(_servos[arrayPos1]->getPin(), 0, _servos[arrayPos1]->getActualPos()+i*(step1/abs(step1)));
    }
    if(i <= abs(step2)){
      _driver->setPWM(_servos[arrayPos2]->getPin(), 0, _servos[arrayPos2]->getActualPos()+i*(step2/abs(step2)));
    }
    else{}
    delay(20);
  }
  _servos[arrayPos1]->setActualPos(_servos[arrayPos1]->getActualPos()+step1);
  _servos[arrayPos2]->setActualPos(_servos[arrayPos2]->getActualPos()+step2);
}

void ESERVODRIVER::moveFourServoTo(short servoPin1, short servoPin2, short servoPin3, short servoPin4, short step1, short step2, short step3, short step4){
  short arrayPos1 = tryFindServo(servoPin1);
  short arrayPos2 = tryFindServo(servoPin2);
  short arrayPos3 = tryFindServo(servoPin3);
  short arrayPos4 = tryFindServo(servoPin4);

  short bgStep = max(abs(step1), abs(step2));
  bgStep = max(abs(bgStep), abs(step3));
  bgStep = max(abs(bgStep), abs(step4));

  for(int i = 1; i <= bgStep; i++){
    if (i <= abs(step1)){
      _driver->setPWM(_servos[arrayPos1]->getPin(), 0, _servos[arrayPos1]->getActualPos()+i*(step1/abs(step1)));
    }
    if(i <= abs(step2)){
      _driver->setPWM(_servos[arrayPos2]->getPin(), 0, _servos[arrayPos2]->getActualPos()+i*(step2/abs(step2)));
    }
    if(i <= abs(step3)){
      _driver->setPWM(_servos[arrayPos3]->getPin(), 0, _servos[arrayPos3]->getActualPos()+i*(step3/abs(step3)));
    }
    if(i <= abs(step4)){
      _driver->setPWM(_servos[arrayPos4]->getPin(), 0, _servos[arrayPos4]->getActualPos()+i*(step4/abs(step4)));
    }
    else{}
    delay(30);
  }
  _servos[arrayPos1]->setActualPos(_servos[arrayPos1]->getActualPos()+step1);
  _servos[arrayPos2]->setActualPos(_servos[arrayPos2]->getActualPos()+step2);
  _servos[arrayPos3]->setActualPos(_servos[arrayPos3]->getActualPos()+step3);
  _servos[arrayPos4]->setActualPos(_servos[arrayPos4]->getActualPos()+step4);
}


short ESERVODRIVER::tryFindServo(short &pin){
  for (int i = 0; i < SERVO_COUNT; i++){
    if (_servos[i]->getPin() == pin){
      return i;
    }
  }
  return -1;
}
ESERVODRIVER::~ESERVODRIVER(){

}