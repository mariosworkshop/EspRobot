#include "Display.h"
//#include "Encoder.h"

Display *display;
//Encoder *encoder;

void setup() {
  Serial.begin(9600);
  display = new Display();
  //encoder = new Encoder();
}

void loop() {
  //encoder->checkEncoder();
 // Serial.println("Button: " + String(encoder->getButtonState()));
//  Serial.println("Encoder: " + String(encoder->getEncoderState()));
//  delay(10);
}