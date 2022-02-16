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
};
#endif
