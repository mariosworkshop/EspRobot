#include "SERVOControl.h"

SERVOControl::SERVOControl(){
  _pwm = new Adafruit_PWMServoDriver();
  _pwm->begin();
  _pwm->setOscillatorFrequency(27000000);
  _pwm->setPWMFreq(SERVO_FREQ);
  delay(10);

  initServos();
  printServosInfo();
}

void SERVOControl::initServos(){
  SPIFFS.begin();
  _file = new File();
  *_file = SPIFFS.open(FILE_NAME, "r");
  unsigned char arrayPos = 0;

  _file->readStringUntil('\n');
  while(_file->available()){
    _servo[arrayPos] = new ServoJoint(READ_NUM(), READ_NUM(), 0, READ_NUM(), _file->readStringUntil('\n').toInt());
    moveSingleServo(_servo[arrayPos]->getServoPin(), _servo[arrayPos]->getMidServoPos());
    arrayPos++;
  }
  delete _file;
  SPIFFS.end();
}

void SERVOControl::printServosInfo(){
  Serial.println("");
  for (int i = 0; i < SERVO_COUNT; i++){
    Serial.println("Pin: " + String(_servo[i]->getServoPin()) + " - "
    + "Stred: " + String(_servo[i]->getMidServoPos()) + " - "
    + "Akt: " + String(_servo[i]->getActServoPos()) + " - "
    + "Max: " + String(_servo[i]->getMaxServoPos()) + " - "
    + "Min: " + String(_servo[i]->getMinServoPos()));
  }
}

void SERVOControl::moveFourServos(unsigned char servoPins[4], short servosSteps[4]){

}

void SERVOControl::moveSingleServo(unsigned char pin, unsigned char pos){
  _pwm->setPWM(pin, 0, degreeToPulse(pos));
}

unsigned char SERVOControl::tryFindServo(unsigned char pin){
  for (int i = 0; i < SERVO_COUNT; i++){
    if(_servo[i]->getServoPin() == pin){ return i; }
  }
  return NULL;
}

short SERVOControl::degreeToPulse(int degree){
  return map(degree, 0, 180, SERVOMIN, SERVOMAX);
}

SERVOControl::~SERVOControl(){
  for (int i = 0; i < SERVO_COUNT; i++){ delete _servo[i]; }
  delete _file, _pwm;
}