#include "esteira.h"
#include "sensor.h"
#include "serial_comm.h"


Sensor sensor1;
Sensor sensor2;

Esteira esteira;
Serial_comm serial;

//boolean verificaMensagem();

void setup ()
{
  Serial.begin(9600);
  Serial.println("start....");
}

void loop()
{
  serial.getJson();

  if (serial.from == "M1" && serial.state == "atM1") {
    esteira.power = false;
    int s1 = sensor1.estadoSensor(4);
    Serial.println("sensor 1 leu ");
    serial.sendJson("s1", "nearM1");
    serial.from = "0";
    serial.state = "0";
  }

  if (serial.from == "M2" && serial.state == "onS2") {
    esteira.power = true;
    int s2 = sensor2.estadoSensor(5);
    Serial.print("sensor 2 leu ");
    serial.sendJson("s2", "nearM2");
    serial.from = "0";
    serial.state = "0";
  }

  esteira.Run(1000, HIGH);
}

//boolean verificaMensagem() {
//  if (serial.from == "M1" && serial.state == "atM1")
//  {
//    return true;
//  }
//
//  if (serial.from == "M2" && serial.state == "onS2")
//  {
//    return true;
//  }
//
//  return false;
//}
