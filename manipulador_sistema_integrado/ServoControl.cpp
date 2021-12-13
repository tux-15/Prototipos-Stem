#include "ServoControl.h"

ServoControl::ServoControl(){};

ServoControl::~ServoControl(){/* ¯\_(ツ)_/¯ */};

void ServoControl::startPosition(){
  Serial.println("Start Position");
  this->servo1.write(90);
  this->servo2.write(90);
  this->servo3.write(90);
  this->servo4.write(90);
  this->servo5.write(30);
  delay(500);
};

void ServoControl::effector(String state){
  if(state == "open") this->servo5.write(30);
  else if (state == "close") this->servo5.write(65);
};

void ServoControl::attachServos(){
  Serial.println("Attaching");
  this->servo1.attach(4);
  this->servo2.attach(5);
  this->servo3.attach(6);
  this->servo4.attach(7);
  this->servo5.attach(8);
  delay(250);
};

void ServoControl::doTrajectory(const float trajetoria[][4], int sizeOfTrajectory) {
  for (int i = 0; i < sizeOfTrajectory; i++) {
    //Serial.println();
    for (int j = 0; j < 4; j++) {
      this->servos[j].write(trajetoria[i][j]);
      //Serial.println(trajetoria[i][j]);
    }; delay(80);
  };
//  trajetoria = NULL;
};
