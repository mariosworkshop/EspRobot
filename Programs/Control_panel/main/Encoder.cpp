#include "Encoder.h"

Encoder::Encoder(){
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(ENCODER_R_PIN, INPUT_PULLUP);
  pinMode(ENCODER_L_PIN, INPUT_PULLUP);
  _buttonState = false;
  _encoderState = 0;
}

void Encoder::checkEncoder(){
  _buttonState = !digitalRead(SWITCH_PIN);

  if(digitalRead(ENCODER_R_PIN) > digitalRead(ENCODER_L_PIN)){
    _encoderState = 1;
  }
  else if (digitalRead(ENCODER_R_PIN) < digitalRead(ENCODER_L_PIN)){
    _encoderState = -1;
  }
  else{
    _encoderState = 0;
  }
}

bool Encoder::getButtonState(){
  return _buttonState;
}

int Encoder::getEncoderState(){
  return _encoderState;
}

Encoder::~Encoder(){
}