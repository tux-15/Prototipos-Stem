#include "sensor.h"

Sensor::Sensor(){
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  };

Sensor::~Sensor(){};

byte Sensor::estadoSensor(byte sensor){
  return digitalRead(sensor);
};
