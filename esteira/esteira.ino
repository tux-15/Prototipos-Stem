#include "esteira.h"
#include "sensor.h"
#include "utils.h"


Sensor sensor1;
Sensor sensor2;

Esteira esteira;
Utils utils;

void setup ()
{
  Serial.begin(9600);
}

void loop()
{ 
  int s1 = sensor1.estadoSensor(4);
  int s2 = sensor2.estadoSensor(5);
  
  utils.getJson();

  if (verificaMensagem() == true && s1 == 0) {
    esteira.power = true;
  }

  if (s2 == 0) {
    esteira.power = false;
  }

    esteira.Run(1000, HIGH);
}


boolean verificaMensagem() {
  if (utils.meta == "M1" && utils.passo == 4 && utils.estado == "1")
  {
    return true;
  }

  return false;
}
