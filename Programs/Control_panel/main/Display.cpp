#include "Display.h"

Display::Display(){
  oled = new Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);
  encoder = new Encoder();

  while(!oled->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    LOG("Display failed!");
    delay(300);
  }
  LOG("Display success!");
  initDisplay();
  controlScreen();
}
void Display::initDisplay(){
  oled->clearDisplay();
  oled->drawBitmap(0, 0, openingScreen, 128, 64, 1);
  oled->display();
  delay(2000);
  for(int i = 0; i <= DISPLAY_HEIGHT; i++){
    oled->clearDisplay();
    oled->drawBitmap(0, -i, openingScreen, 128, 64, 1);
    oled->display();
    delay(5);
  }
  LOG("Hotovo");
}
void Display::controlScreen(){
  oled->clearDisplay();
  oled->drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 1);
  oled->drawRect(12, 24, 40, 16, 1);
  oled->drawRect(76, 24, 40, 16, 1);
  oled->display();
  while(1){
    encoder->checkEncoder();
    if(encoder->getEncoderState() == 1){
      oled->fillRect(12, 24, 40, 16, 1);
      oled->fillRect(76, 24, 40, 16, 0);
      oled->drawRect(76, 24, 40, 16, 1);
      oled->display();
    }
    else if(encoder->getEncoderState() == -1){
      oled->fillRect(12, 24, 40, 16, 0);
      oled->drawRect(12, 24, 40, 16, 1);
      oled->fillRect(76, 24, 40, 16, 1);
      oled->display();
    }
    else if(encoder->getButtonState()){
      oled->clearDisplay();
      oled->display();
      break;
    }
    else{}
  }
}
Display::~Display(){
}