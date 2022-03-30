#include "motores.h",
#include "serial_comm.h"

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
//Lado esquerdo
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Serial_comm serial;

Motores::Motores(){
};

Motores::~Motores(){};

void Motores::motorSpeedD(int pwm, int valor){
    motor1.run(valor);
    motor2.run(valor);
    motor1.setSpeed(pwm);
    motor2.setSpeed(pwm);
};

void Motores::motorSpeedE(int pwm, int valor){
    motor3.run(valor);
    motor4.run(valor);
    motor3.setSpeed(pwm);
    motor4.setSpeed(pwm);
};

void Motores::controle() {
    serial.getJson();
  if (serial.angle > 70 and serial.angle < 110) {
    this->velocidadeD = map(serial.speed, 0, 100, 0, 255) + 2;
    this->velocidadeE = map(serial.speed, 0, 100, 0, 255);
    motorSpeedE(this->velocidadeD, FORWARD);
    motorSpeedD(this->velocidadeE, FORWARD);
  }

  //Trás
  if (serial.angle > 250 and serial.angle < 290) {
    this->velocidadeD = map(serial.speed, 0, 100, 0, 255) + 2;
    this->velocidadeE = map(serial.speed, 0, 100, 0, 255);
    motorSpeedE(this->velocidadeD, BACKWARD);
    motorSpeedD(this->velocidadeE, BACKWARD);
  }

  //Esquerda frente
  if (serial.angle > 110 and serial.angle < 180) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
   this-> velocidadeD = 150 + this->Xdif;
    this->velocidadeE = 160 - this->Xdif * 0.5;
    motorSpeedE(this->velocidadeD, FORWARD);
    motorSpeedD(this->velocidadeE, FORWARD);
  }

  //Esquerda trás
  if (serial.angle > 180 and serial.angle < 250) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 150 + this->Xdif;
    this->velocidadeE = 170 - this->Xdif*0.25;
    motorSpeedE(this->velocidadeD, BACKWARD);
    motorSpeedD(this->velocidadeE, BACKWARD);
  }

  //Direita frente
  if (serial.angle > 0 and serial.angle < 80) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 150 - this->Xdif * 0.75;
    this->velocidadeE = 160 + this->Xdif;
    motorSpeedE(this->velocidadeD, FORWARD);
    motorSpeedD(this->velocidadeE, FORWARD);
  }

  //Direita trás
  if (serial.angle > 290 and serial.angle < 360) {
   this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 150 - this->Xdif * 0.75;
    this->velocidadeE = 160 + this->Xdif;
    motorSpeedE(this->velocidadeD, BACKWARD);
    motorSpeedD(this->velocidadeE, BACKWARD);
  }

  //Parar
  if (serial.speed < 20) {
    motorSpeedE(0, RELEASE);
    motorSpeedD(0, RELEASE);
  }

  if (this->velocidadeD > 255) {
    this->velocidadeD = 255;
  }

  if (this->velocidadeE > 255) {
    this->velocidadeE = 255;
  }

  if (this->velocidadeD < 0) {
    this->velocidadeD = 0;
  }

  if (this->velocidadeE < 0) {
    this->velocidadeE = 0;
  }
};
