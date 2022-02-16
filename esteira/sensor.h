#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class Sensor
{
  private:
    byte s1 = 4;
    byte s2 = 5;

  public:
    Sensor();
    ~Sensor();
    byte estadoSensor(byte sensor);

};
#endif
