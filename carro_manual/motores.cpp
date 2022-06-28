#include "motores.h"
#include "serial_comm.h"

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
//Lado esquerdo
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Serial_comm serial;

Motores::Motores() {
};

Motores::~Motores() {};

void Motores::setup_handShake() {
  serial.setHandshakeInterval(1000);
  serial.setType("carrinho");

  serial.waitHandshake("ARD", serial.getType(), "ESP", "OK");
};

void Motores::motorSpeedD(int pwm, int valor) {
  motor1.run(valor);
  motor2.run(valor);
  motor1.setSpeed(pwm);
  motor2.setSpeed(pwm);
};

void Motores::motorSpeedE(int pwm, int valor) {
  motor3.run(valor);
  motor4.run(valor);
  motor3.setSpeed(pwm);
  motor4.setSpeed(pwm);
};

void Motores::controle() {
  
    serial.getJson();
    
    int velocidade = serial.from.toInt();
    int angulo = serial.state.toInt();

  //Frente
  if (angulo > 75 and angulo < 105) {
    this->velocidadeD = map(velocidade, 20, 100, 0, 255);
    this->velocidadeE = map(velocidade, 20, 100, 0, 255);
    this->sentido = FORWARD;
  }

  //Trás
  if (angulo > 255 and angulo < 285) {
    this->velocidadeD = map(velocidade, 20, 100, 0, 255);
    this->velocidadeE = map(velocidade, 20, 100, 0, 255);
    this->sentido = BACKWARD;
  }

  //Esquerda brusca
  if (angulo > 165 and angulo < 195) {
    this->velocidadeD = map(velocidade, 20, 100, 0, 255);
    this->velocidadeE = 0;
    this->sentido = FORWARD;
  }

  //Direita Brusca
  if (angulo > 345 || angulo < 15) {
    this->velocidadeD = 0;
    this->velocidadeE = map(velocidade, 20, 100, 0, 255);
    this->sentido = FORWARD;
  }

  //Esquerda frente
  if (angulo > 105 and angulo < 175) {
    this->Xdif = map(velocidade, 20, 100, 0, 150);
    this->velocidadeD = 180 + this->Xdif;
    this->velocidadeE = 150 - this->Xdif * 0.5;
    this->sentido = FORWARD;
  }

  //Esquerda trás
  if (angulo > 195 and angulo < 255) {
    this->Xdif = map(velocidade, 20, 100, 0, 150);
    this->velocidadeD = 180 + this->Xdif;
    this->velocidadeE = 150 - this->Xdif * 0.5;
    this->sentido = BACKWARD;
  }

  //Direita frente
  if (angulo > 15 and angulo < 75) {
    this->Xdif = map(velocidade, 20, 100, 0, 150);
    this->velocidadeD = 170 - this->Xdif * 0.75;
    this->velocidadeE = 180 + this->Xdif;
    this->sentido = FORWARD;
  }

  //Direita trás
  if (angulo > 285 and angulo < 345) {
    this->Xdif = map(velocidade, 20, 100, 0, 150);
    this->velocidadeD = 170 - this->Xdif * 0.75;
    this->velocidadeE = 180 + this->Xdif;
    this->sentido = BACKWARD;
  }

  //Parar
  if (velocidade < 20) {
    this->velocidadeD = 0;
    this->velocidadeE = 0;
    this->sentido = RELEASE;
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

  motorSpeedE(this->velocidadeE, this->sentido);
  motorSpeedD(this->velocidadeD, this->sentido);
};
