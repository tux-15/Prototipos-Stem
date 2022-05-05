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
    
   //Frente
  if (serial.angle > 75 and serial.angle < 105) {
    this->velocidadeD = map(serial.speed, 0, 100, 0, 255);
    this->velocidadeE = map(serial.speed, 0, 100, 0, 255);
    this->sentido = FORWARD;
  }

  //Trás
  if (serial.angle > 255 and serial.angle < 285) {
    this->velocidadeD = map(serial.speed, 0, 100, 0, 255);
    this->velocidadeE = map(serial.speed, 0, 100, 0, 255);
    this->sentido = BACKWARD;
  }

   //Esquerda brusca
  if (serial.angle > 165 and serial.angle < 195) {
    this->velocidadeD = map(serial.speed, 0, 100, 0, 255);
    this->velocidadeE = 0;
    this->sentido = FORWARD;
  }

  //Direita Brusca
  if (serial.angle > 345 || serial.angle < 15) {
    this->velocidadeD = 0;
    this->velocidadeE = map(serial.speed, 0, 100, 0, 255);
    this->sentido = FORWARD;
  }

  //Esquerda frente
  if (serial.angle > 105 and serial.angle < 175) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 180 + this->Xdif;
    this->velocidadeE = 150 - this->Xdif * 0.5;
    this->sentido = FORWARD;
  }

  //Esquerda trás
  if (serial.angle > 195 and serial.angle < 255) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 180 + this->Xdif;
    this->velocidadeE = 150 - this->Xdif*0.5;
    this->sentido = BACKWARD;
  }

  //Direita frente
  if (serial.angle > 15 and serial.angle < 75) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 170 - this->Xdif * 0.75;
    this->velocidadeE = 180 + this->Xdif;
    this->sentido = FORWARD;
  }

  //Direita trás
  if (serial.angle > 285 and serial.angle < 345) {
    this->Xdif = map(serial.speed, 0, 100, 0, 150);
    this->velocidadeD = 170 - this->Xdif * 0.75;
    this->velocidadeE = 180 + this->Xdif;
    this->sentido = BACKWARD;
  }

  //Parar
  if (serial.speed < 10) {
    this->velocidadeD = 0;
    this->velocidadeE = 0;
    this->sentido = RELEASE;
  }

  if (this->velocidadeD > 255) {this->velocidadeD = 255;}
  if (this->velocidadeE > 255) {this->velocidadeE = 255;}
  if (this->velocidadeD < 0) { this->velocidadeD = 0;}
  if (this->velocidadeE < 0) {this->velocidadeE = 0;}

    motorSpeedE(this->velocidadeE, this->sentido);
    motorSpeedD(this->velocidadeD, this->sentido);
};
