#include "esteira.h"
#include "sensor.h"
#include "serial_comm.h"

#define serialArduino Serial

Sensor sensor1;
Sensor sensor2;

Esteira esteira;
Serial_comm serial;

boolean passo = true;

void setup ()
{
  serialArduino.begin(9600);
  serialArduino.println("start esteira code....");
  serialArduino.println("Fim do setup");
}

void loop()
{
  serial.getJson();

  int s1 = sensor1.estadoSensor(4);
  int s2 = sensor2.estadoSensor(5);

  if (s1 == 0) {
    if (passo == true) {
      esteira.power = false;
      serialArduino.println("Objeto detectado em S1...");
      passo = false;
    }

    if (serial.from == "car" && serial.state == "atM1") {
      serial.sendJson("s1", "nearM1");
      serialArduino.println("Mensagem enviada para M1...");
      serial.from = "0"; serial.state = "0";
    }
  }

  if (s2 == 0) {
    if (passo == false) {
      serialArduino.println("Objeto detectado em S2...");
      passo = true;
    }

    if (serial.from == "M2" && serial.state == "onS2") {
      serial.sendJson("s2", "nearM2");
      serialArduino.println("Mensagem enviada para carro...");
      esteira.power = true;
      serial.from = "0"; serial.state = "0";
    }
  }

  esteira.Run(3000, HIGH);
}
