#include "PS2_remote.h"

PS2_remote::PS2_remote(){
  _ps2 = new PS2X();
  if(_ps2->config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DATA, false, false) == 0){
    LOG("\nReceiver found!");
  }
  else{
    LOG("\nReceiver was not found!");
  }
}

bool PS2_remote::isPressed(int key){
  _ps2->read_gamepad(false, 0);
  if(_ps2->Button(key)){
    return true;
  }
  return false;
}

int PS2_remote::readJoystick(int key){
  _ps2->read_gamepad(false, 0);
  return _ps2->Analog(key);
}

PS2_remote::~PS2_remote(){
  
}