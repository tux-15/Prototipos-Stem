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
    this->servo5.write(this->effectorOpen);
    Serial.println("effector open");
  }
  else if (state == "close"){
    this->servo5.write(this->effectorClosed);
    Serial.println("effector closed");
  }
};

void ServoControl::setEffectorAngles(int effectorOpen, int effectorClosed){
  this->effectorOpen = effectorOpen;
  this->effectorClosed = effectorClosed;
}

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

void ServoControl::moveServo(String servo, String angle){

  int servoAngle = angle.toInt();

  if(servo == "value0"){
    this->servo1.write(servoAngle);
  }

  if(servo == "value1"){
    this->servo2.write(servoAngle);
  }

  if(servo == "value2"){
    this->servo3.write(servoAngle);
  }

  if(servo == "value3"){
    this->servo4.write(servoAngle);
  }
  
  if(servo == "effector"){
    if(this->effectorStatus == true) this->effector("close");
    else if(this->effectorStatus == false) this->effector("open");
    effectorStatus = !effectorStatus;
  }
};
