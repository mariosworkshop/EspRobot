#include "ServoControl.h"

ServoControl::ServoControl(){
  _pwm = new Adafruit_PWMServoDriver();
  _pwm->begin();
  _pwm->setOscillatorFrequency(27000000);
  _pwm->setPWMFreq(SERVO_FREQ);
  delay(10);

  _rServo = new ReadServo(0, 0, 0, 0, 0);

  initServos();
  printServosInfo();  //Uncomment, if you want to write down everything about servos
}

void ServoControl::initServos(){
  LittleFS.begin();
  _file = new File();
  *_file = LittleFS.open(FILE_NAME, "r");
  unch arrayPos = 0;

  readFSUntil('\n');

  while(_file->available()){
    _servo[arrayPos] = new ServoJoint(readFSUntil(' '), readFSUntil(' '), _rServo->readValue(_servo[arrayPos]->getServoPin()), readFSUntil(' '), readFSUntil('\n'), SERVO_STEP);
    _servo[arrayPos]->setEstimatedPosition(_servo[arrayPos]->getMidServoPos());
    arrayPos++;
  }
  LittleFS.end();
  delete _rServo;
}

void ServoControl::printServosInfo(){
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

int ServoControl::readFSUntil(char delimiter){
  return _file->readStringUntil(delimiter).toInt();
}

void ServoControl::moveServos(short period) {
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

void ServoControl::setEstimatedPositions(unch estimatedPositions[16]) {
  for(int i = 0; i < 16; i++) {
    _servo[i]->setEstimatedPosition(estimatedPositions[i] - (SERVO_MID - _servo[i]->getMidServoPos()));
    LOG("\n" + String(i) + " " + String(_servo[i]->getEstimatedPosition()));
  }
  needMove = true;
}

ServoControl::~ServoControl(){
  for (int i = 0; i < SERVO_COUNT; i++){ delete _servo[i]; }
  //delete _file, _pwm;
}