#include "SERVOControl.h"

SERVOControl::SERVOControl(){
  _pwm = new Adafruit_PWMServoDriver();
  _pwm->begin();
  _pwm->setOscillatorFrequency(27000000);
  _pwm->setPWMFreq(SERVO_FREQ);
  delay(10);

  initServos();
  printServosInfo();  //Odkomentuj, keď chceš vypísať všetky dáta o servách
}

void SERVOControl::initServos(){
  LittleFS.begin();
  _file = new File();
  *_file = LittleFS.open(FILE_NAME, "r");
  unch arrayPos = 0;

  readFSUntil('\n');

  while(_file->available()){
    _servo[arrayPos] = new ServoJoint(readFSUntil(' '), readFSUntil(' '), 90, readFSUntil(' '), readFSUntil('\n'), SERVO_STEP);
    _servo[arrayPos]->setEstimatedPosition(_servo[arrayPos]->getMidServoPos());
    arrayPos++;
  }
  LittleFS.end();
}

void SERVOControl::printServosInfo(){
  Serial.println("");
  for (int i = 0; i < SERVO_COUNT; i++){
    Serial.println("Pin: " + String(_servo[i]->getServoPin()) + " - "
    + "Stred: " + String(_servo[i]->getMidServoPos()) + " - "
    + "Akt: " + String(_servo[i]->getActServoPos()) + " - "
    + "Max: " + String(_servo[i]->getMaxServoPos()) + " - "
    + "Min: " + String(_servo[i]->getMinServoPos()));
    char temp = _servo[i]->getMinServoPos();
    Serial.println(temp);
  }
}

int SERVOControl::readFSUntil(char delimiter){
  return _file->readStringUntil(delimiter).toInt();
}

void SERVOControl::moveServos(short period) {
   //if (needMove == false) {return;}    
    bool changeNeedMove = false;
    for (int i = 0; i < 16; i++) {
        if (_servo[i]->makeStep(_pwm)) {
            changeNeedMove = true;
        }        
    }
    delay(period);
    needMove = changeNeedMove;
}

void SERVOControl::setEstimatedPositions(unch estimatedPositions[16]) {
  for(int i = 0; i < 16; i++) {
    _servo[i]->setEstimatedPosition(estimatedPositions[i] - (SERVO_MID - _servo[i]->getMidServoPos()));
    //Serial.println(String(i) + " " + String(_servo[i]->getEstimatedPosition()));
  }
  needMove = true;
}

SERVOControl::~SERVOControl(){
  for (int i = 0; i < SERVO_COUNT; i++){ delete _servo[i]; }
  delete _file, _pwm;
}