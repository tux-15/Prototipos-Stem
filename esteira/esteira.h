#ifndef ESTEIRA_H
#define ESTEIRA_H
#include <Arduino.h>

class Esteira
{
  private:
    const int stepPin = 2;
    const int dirPin = 3;
    int meioPeriodo;

  public:
    Esteira();
    ~Esteira();
    void Run(int meioPeriodo, boolean direcao);
    boolean power;
};
#endif
