#include "sensores.h"

#define SerialESP Serial2
//#define SerialESP Serial

Sensores::Sensores() {
  pinMode(this->s1, INPUT);
  pinMode(this->s2, INPUT);
  pinMode(this->s3, INPUT);
  pinMode(this->s4, INPUT);
  pinMode(this->s5, INPUT);
};

Sensores::~Sensores() {};

int Sensores::readSensors() {
  this->sensor[0] = !digitalRead(s1);
  this->sensor[1] = !digitalRead(s2);
  this->sensor[2] = !digitalRead(s3);
  this->sensor[3] = !digitalRead(s4);
  this->sensor[4] = !digitalRead(s5);

  if (this->estado == true) {

    if (this->sensor[0] == 0 && this->sensor[1] == 0 && this->sensor[2] == 0 && this->sensor[3] == 0 && this->sensor[4] == 0) {
      return 7;
    }

    if (this->sensor[0] == 0 && this->sensor[1] == 0 && this->sensor[2] == 0 && this->sensor[3] == 0 && this->sensor[4] == 1) {
      return 1;
    }

    if (this->sensor[0] == 0 && this->sensor[1] == 0 && this->sensor[2] == 0 && this->sensor[3] == 1 && this->sensor[4] == 0) {
      return 2;
    }

    if (this->sensor[0] == 0 && this->sensor[1] == 0 && this->sensor[2] == 1 && this->sensor[3] == 0 && this->sensor[4] == 0) {
      return 3;
    }

    if (this->sensor[0] == 0 && this->sensor[1] == 1 && this->sensor[2] == 0 && this->sensor[3] == 0 && this->sensor[4] == 0) {
      return 4;
    }

    if (this->sensor[0] == 1 && this->sensor[1] == 0 && this->sensor[2] == 0 && this->sensor[3] == 0 && this->sensor[4] == 0) {
      return 5;
    }
  }

  if (this->sensor[0] == 1 && this->sensor[1] == 1 && this->sensor[3] == 1){ //&& this->sensor[4] == 1) {
    this->estado = false;
    return 6;
  }

  else return 0;

};

void Sensores::debug() {
  SerialESP.println(sensor[0]);
  SerialESP.println(sensor[1]);
  SerialESP.println(sensor[2]);
  SerialESP.println(sensor[3]);
  SerialESP.println(sensor[4]);
  delay(500);
};
