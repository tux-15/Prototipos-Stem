#ifndef SENSORES_H
#define SENSORES_H
#include <Arduino.h>

class Sensores
{
  private:
    byte s1 = 42;
    byte s2 = 40;
    byte s3 = 38;
    byte s4 = 36;
    byte s5 = 34;

    
    byte sensor[5] = {0, 0, 0, 0, 0};
//
//    const int s1 = 22;
//    const int s2 = 24;
//    const int s3 = 26;
//    const int s4 = 28;
//    const int s5 = 30;

  public:
    Sensores();
    ~Sensores();
    
    int readSensors();
    void debug();

    boolean estado = false;
};
#endif
