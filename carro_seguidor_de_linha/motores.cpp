#include "motores.h"

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
//Lado esquerdo
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

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
