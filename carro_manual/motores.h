#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>
#include <AFMotor.h>

class Motores
{
  private:
   
  public:
    Motores();
    ~Motores();

    void motorSpeedD(int pwm, int valor);
    void motorSpeedE(int pwm, int valor);
    void controle();

    int velocidade = 0;
    int angulo = 0;
    int velocidadeD = 0;
    int velocidadeE = 0;
    int Xdif = 0;
    int sentido = 0;

};
#endif
