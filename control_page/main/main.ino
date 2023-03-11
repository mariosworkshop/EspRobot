#include <ESP8266WebServer.h>
#include <LittleFS.h>

#include "ServoControl.h"
#include "PS2_remote.h"
#include "Gyro.h"

ServoControl *driver;
PS2_remote *ps2;
Gyro *mpu;

int speed = 30;
String servos_pos = "";

unch positions[SERVO_COUNT] = {90, 130, 50, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 130, 50, 90};

ESP8266WebServer server(80);

void handleRoot() {
  File readHTML = LittleFS.open("/index.html", "r");  
  server.send(200, "text/html", readHTML.readString());
  readHTML.close();
}

void handleJS(){
  File readJS = LittleFS.open("/script.js", "r");    
  server.send(200, "text/javascript", readJS.readString());
  readJS.close();
}

void handleServos(){
  servos_pos = server.arg("servoPOS");

  //Serial.println("Servos positions: " + servos_pos);
  parseServer(',');
  server.send(200, "text/plane", "");
}

void setup(){
  Serial.begin(115200);
  driver = new ServoControl();
  ps2 = new PS2_remote();
  mpu = new Gyro();

  driver->setEstimatedPositions(positions);

  if(!LittleFS.begin()){
    Serial.println("\nFS not working!");
    return;
  }
  
  WiFi.begin("Jokohome-2", "2x8G6a1Oo");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("Jokohome-2");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/script.js", handleJS);
  server.on("/setPOS", handleServos);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  driver->setEstimatedPositions(positions);
  mpu->readValues();
  
  if(!driver->getNeedMove()){
    /*if(Serial.available() > 0){
      parseSerial(',');
    }*/
    driver->setEstimatedPositions(positions);
  }
  driver->moveServos(speed);

  server.handleClient();
}

void parseSerial(char delimiter){
  String data = Serial.readString();
  LOG(data + "\n");

  String dataPart= "";
  int arrPos = 0;

  for(char sign : data){
    if(sign != delimiter){
      dataPart += sign;
    }
    else{
      positions[arrPos] = dataPart.toInt();
      LOG(String(arrPos) + " - " + String(positions[arrPos]) + "\n");
      dataPart = "";
      arrPos++;
    }
  }
}

void parseServer(char delimiter){
  LOG(servos_pos + "\n");

  String dataPart= "";
  int arrPos = 0;

  for(char sign : servos_pos){
    if(sign != delimiter){
      dataPart += sign;
    }
    else{
      positions[arrPos] = dataPart.toInt();
      LOG(String(arrPos) + " - " + String(positions[arrPos]) + "\n");
      dataPart = "";
      arrPos++;
    }
  }
  positions[arrPos] = dataPart.toInt();
  LOG(String(arrPos) + " - " + String(positions[arrPos]) + "\n");
}
/*
void reactToPs2(){
    
  int value = ps2->readJoystick(PSS_LY);
  speed = map(value, 0, 255, 30, 500);

  if(ps2->isPressed(PSB_TRIANGLE)){
    positions[1] = 90;
    positions[2] = 90;
    positions[13] = 90;
    positions[14] = 90;
  }
  else if(ps2->isPressed(PSB_CROSS)){
    positions[1] = 130;
    positions[2] = 50;
    positions[13] = 130;
    positions[14] = 50;
  }
  else if(ps2->isPressed(PSB_SQUARE)){
    positions[0] = 100;
    positions[4] = 95;
    positions[11] = 95;
    positions[15] = 100;
  }
  else if(ps2->isPressed(PSB_CIRCLE)){
    positions[0] = 80;
    positions[4] = 85;
    positions[11] = 85;
    positions[15] = 80;
  }
  else{}
}*/