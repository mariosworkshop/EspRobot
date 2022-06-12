#include "SERVOControl.h"

SERVOControl::SERVOControl(){
  _pwm = new Adafruit_PWMServoDriver();
  _pwm->begin();
  _pwm->setOscillatorFrequency(27000000);
  _pwm->setPWMFreq(SERVO_FREQ);
  delay(10);

  initServos();
  //printServosInfo();  //Odkomentuj, keď chceš vypísať všetky dáta o servách
}

void SERVOControl::initServos(){
  SPIFFS.begin();
  _file = new File();
  *_file = SPIFFS.open(FILE_NAME, "r");
  unch arrayPos = 0;

  readFSUntil('\n');
  while(_file->available()){
    _servo[arrayPos] = new ServoJoint(readFSUntil(' '), readFSUntil(' '), 0, readFSUntil(' '), readFSUntil('\n'));
    _servo[arrayPos]->setActServoPos(_servo[arrayPos]->getMidServoPos());
    moveToPos(_servo[arrayPos]->getServoPin(), _servo[arrayPos]->getMidServoPos(), 0);
    arrayPos++;
  }
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

int SERVOControl::readFSUntil(char delimiter){
  return _file->readStringUntil(delimiter).toInt();
}

void SERVOControl::moveToPos(unch pin, unch pos, short period){
  ServoJoint *servo = tryFindServo(pin);
  if(servo == nullptr){ return; }
  if (servo->getActServoPos() < pos){
    for(int i = servo->getActServoPos(); i <= pos + 0 - (SERVO_MID - servo->getMidServoPos()); i++){
      _pwm->setPWM(pin, 0, degreeToPulse(i));
      delay(period);
    }
  }
  else{
    for(int i = servo->getActServoPos(); i >= pos + 0 - (SERVO_MID - servo->getMidServoPos()); i--){
      _pwm->setPWM(pin, 0, degreeToPulse(i));
      delay(period);
    }
  }
  servo->setActServoPos(pos);
}

void SERVOControl::moveToPos(unch pin1, unch pin2, unch pos, short period){
  ServoJoint* servo[] = {tryFindServo(pin1), tryFindServo(pin2)};
  ServoJoint *servoResult = tryFindBiggActServo(servo);

  if (servoResult->getActServoPos() < pos){
    for(int i = servoResult->getActServoPos(); i <= pos; i++){
      if(servo[0]->getActServoPos() != pos + 0 - (SERVO_MID - servo[0]->getMidServoPos())){
        _pwm->setPWM(pin1, 0, degreeToPulse(i));
      }
      if(servo[1]->getActServoPos() != pos + 0 - (SERVO_MID - servo[1]->getMidServoPos())){
        _pwm->setPWM(pin2, 0, degreeToPulse(i));
      }
      delay(period);
    }
  }
  else{
    for(int i = servoResult->getActServoPos(); i >= pos; i--){
      if(servo[0]->getActServoPos() != pos + 0 - (SERVO_MID - servo[0]->getMidServoPos())){
        _pwm->setPWM(pin1, 0, degreeToPulse(i));
      }
      if(servo[1]->getActServoPos() != pos + 0 - (SERVO_MID - servo[1]->getMidServoPos())){
        _pwm->setPWM(pin2, 0, degreeToPulse(i));
      }
      delay(period);
    }
  }
  servo[0]->setActServoPos(pos);
  servo[1]->setActServoPos(pos);
}

void SERVOControl::moveToPos(unch pin1, unch pin2, unch pin3, unch pin4, unch pos, short period){
  ServoJoint* servo[] = {tryFindServo(pin1), tryFindServo(pin2), tryFindServo(pin3), tryFindServo(pin4)};
  ServoJoint *servoResult = tryFindBiggActServo(servo);

  if (servoResult->getActServoPos() < pos){
    for(int i = servoResult->getActServoPos(); i <= pos; i++){
      if(servo[0]->getActServoPos() != pos + 0 - (SERVO_MID - servo[0]->getMidServoPos())){
        _pwm->setPWM(pin1, 0, degreeToPulse(i));
      }
      if(servo[1]->getActServoPos() != pos + 0 - (SERVO_MID - servo[1]->getMidServoPos())){
        _pwm->setPWM(pin2, 0, degreeToPulse(i));
      }
      if(servo[2]->getActServoPos() != pos + 0 - (SERVO_MID - servo[2]->getMidServoPos())){
        _pwm->setPWM(pin3, 0, degreeToPulse(i));
      }
      if(servo[3]->getActServoPos() != pos + 0 - (SERVO_MID - servo[3]->getMidServoPos())){
        _pwm->setPWM(pin4, 0, degreeToPulse(i));
      }
      delay(period);
    }
  }
  else{
    for(int i = servoResult->getActServoPos(); i >= pos; i--){
      if(servo[0]->getActServoPos() != pos + 0 - (SERVO_MID - servo[0]->getMidServoPos())){
        _pwm->setPWM(pin1, 0, degreeToPulse(i));
      }
      if(servo[1]->getActServoPos() != pos + 0 - (SERVO_MID - servo[1]->getMidServoPos())){
        _pwm->setPWM(pin2, 0, degreeToPulse(i));
      }
      if(servo[2]->getActServoPos() != pos + 0 - (SERVO_MID - servo[2]->getMidServoPos())){
        _pwm->setPWM(pin3, 0, degreeToPulse(i));
      }
      if(servo[3]->getActServoPos() != pos + 0 - (SERVO_MID - servo[3]->getMidServoPos())){
        _pwm->setPWM(pin4, 0, degreeToPulse(i));
      }
      delay(period);
    }
  }
  servo[0]->setActServoPos(pos);
  servo[1]->setActServoPos(pos);
  servo[2]->setActServoPos(pos);
  servo[3]->setActServoPos(pos);
}

ServoJoint* SERVOControl::tryFindBiggActServo(ServoJoint* servo[4]){
  ServoJoint* servoMax = servo[0];
  for(int i = 1; i < 4; i++){
    if(servoMax < servo[i]){
      servoMax = servo[i];
    }
  }
  return servoMax;
}

ServoJoint* SERVOControl::tryFindServo(unch pin){
  for (int i = 0; i < SERVO_COUNT; i++){
    if(_servo[i]->getServoPin() == pin){ return _servo[i]; }
  }
  return nullptr;
}

/*void SERVOControl::pohniServami(short period) {
   if (trebaPohnut == false) {return;}    
    bool zmenaTrebaPohnut = false;
    for (int i = 0; i < 12; i++) {
        if (servo[i]->makeStep(_pwm)) {
            zmenaTrebaPohnut = true;
        }        
    }
    delay(period);
    trebaPohnut = zmenaTrebaPohnut;
}

void SERVOControl::setEstimatedPositions(unch estimatedPositions[12]) {
  // [20,0,0,0,0,0,0,0,0,0,0] //["Noha lava chodidlo", "Noha Lava koleno"]
    for(int i = 0; i < 12; i++) {
        setEstimatedPositions(_servo[i]->getActServoPos() + estimatedPositions[i]);
        setEstimatedPositions(estimatedPositions[i]);
    }
    trebaPohnut = true;
}
*/
short SERVOControl::degreeToPulse(int degree){
  return map(degree, 0, 180, SERVOMIN, SERVOMAX);
}

SERVOControl::~SERVOControl(){
  for (int i = 0; i < SERVO_COUNT; i++){ delete _servo[i]; }
  delete _file, _pwm;
}