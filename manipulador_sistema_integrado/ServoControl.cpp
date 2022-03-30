#include "ServoControl.h"
#include "jointStates.h"

ServoControl::ServoControl(){};

ServoControl::~ServoControl(){/* ¯\_(ツ)_/¯ */};

void ServoControl::startPosition(){
  Serial.println("Start Position");
  this->goTo(origin);
  delay(1000);
};

void ServoControl::setServoSpeed(int servoSpeed){
  this->servoSpeed = servoSpeed;
};

void ServoControl::effector(String state){
  if(state == "open") {
//    this->servo5.write(30); //M1
    this->servo5.write(120); //M2
    Serial.println("effector open");
  }//90
  else if (state == "close"){
//     this->servo5.write(75);  //M1
    this->servo5.write(165); //M2 160
    Serial.println("effector closed");
  }
};

void ServoControl::attachServos(){
  Serial.println("Attaching servos");
  this->servo1.attach(4);
  this->servo2.attach(5);
  this->servo3.attach(6);
  this->servo4.attach(7);
  this->servo5.attach(8);
  delay(250);
};

void ServoControl::goTo(const float trajetoria[4]){

  this->servos[0].write(trajetoria[0], this->servoSpeed);
  this->servos[0].wait();
  
  for(int i=0; i<4; i++){
    this->servos[i].write(trajetoria[i], this->servoSpeed);
  };
  for(int i=1; i<4; i++){
    this->servos[i].wait();
  };
};

void ServoControl::moveServo(const char * servo, int angle){
  
  if (strcmp(servo, "value0") == 0){
    this->servo1.write(angle);
  }
  
  if (strcmp(servo, "value1") == 0){
    this->servo2.write(angle);
  }
  
  if (strcmp(servo, "value2") == 0){
    this->servo3.write(angle);
  }
  
  if (strcmp(servo, "value3") == 0){
    this->servo4.write(angle);
  }
  
  if (strcmp(servo, "effector") == 0){
    //this->switchEffector();
  }
};
