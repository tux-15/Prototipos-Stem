#include "serial_comm.h"
#include "motores.h"
#include "sensores.h"
#include "encoder.h"

#define SerialESP Serial2

void verificaMensagem(String from, String state);
void girar180();

Serial_comm serial;
Motores motores;
Sensores sensores;

boolean sentido = true;


void setup() {
  SerialESP.begin(9600);
  while (serial.from != "ws_client" && serial.state != "started") {
    serial.getJson();
  }
  setEncoder();
  sensores.estado = true;
  SerialESP.println("Fim do setup");
  motores.motorSpeedE(100, FORWARD);
  motores.motorSpeedD(103, FORWARD);

}

void loop()
{
  serial.getJson();
  //  calculoVelocidade();
  controle();
  verificaMensagem(serial.from, serial.state);

}

void controle() {
  int retorno = sensores.readSensors();

  switch (retorno) {
    case 0:
      break;

    case 1:
      motores.motorSpeedE(190, FORWARD);
      motores.motorSpeedD(83, FORWARD);
      break;

    case 2:
      motores.motorSpeedE(160, FORWARD);
      motores.motorSpeedD(83, FORWARD);
      break;

    case 3:
      motores.motorSpeedE(100, FORWARD);
      motores.motorSpeedD(103, FORWARD);
      break;

    case 4:
      motores.motorSpeedE(70, FORWARD);
      motores.motorSpeedD(180, FORWARD);
      break;

    case 5:
      motores.motorSpeedE(70, FORWARD);
      motores.motorSpeedD(210, FORWARD);
      break;

    case 6:
      motores.motorSpeedE(0, RELEASE);
      motores.motorSpeedD(0, RELEASE);

      if (sentido == true) {
        serial.sendJson("car", "atM1");
        delay(250);
      }

      if (sentido == false) {
        serial.sendJson("car", "atM2");
        delay(250);
      }
      break;

    case 7:
      motores.motorSpeedE(140, FORWARD);
      motores.motorSpeedD(140, BACKWARD);
      break;

    default:
      break;
  }
}

void verificaMensagem(String from, String state) {
  if (from == "M1" && state == "onCar" ) {
    delay(100);
    sensores.estado = true;
    sentido = false;
    from = "0";
    state = "0";
  }
  if (from == "s2" && state == "nearM2") {
    sensores.estado = true;
    sentido = true;
    from = "0";
    state = "0";
  }
}


void girar180() {
  motores.motorSpeedE(180, FORWARD);
  motores.motorSpeedD(180, BACKWARD);
  delay(1550);
}
