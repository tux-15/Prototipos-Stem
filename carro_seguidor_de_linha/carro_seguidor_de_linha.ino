#include "serial_comm.h"
#include "motores.h"
#include "sensores.h"
#include "encoder.h"

#define serialArduino Serial
#define serialESP Serial2

void verificaMensagem(String from, String state);

Serial_comm serial;
Motores motores;
Sensores sensores;

boolean sentido = true;
boolean passo = true;


void setup() {
  serialArduino.begin(9600);
  serialESP.begin(9600);
  while (serial.from != "ws_client" && serial.state != "started") {
    serial.getJson();
    }
//  setEncoder();
  sensores.estado = true;
  serialArduino.println("Fim do setup");
  serialArduino.println("Start code...");
  motores.motorSpeedE(88, FORWARD);
  motores.motorSpeedD(85, FORWARD);
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
//      motores.motorSpeedE(190, FORWARD);
//      motores.motorSpeedD(83, FORWARD);
      motores.motorSpeedE(185, FORWARD);
      motores.motorSpeedD(70, FORWARD);
      break;

    case 2:
//      motores.motorSpeedE(160, FORWARD);
//      motores.motorSpeedD(83, FORWARD);
      motores.motorSpeedE(150, FORWARD);
      motores.motorSpeedD(83, FORWARD);
      break;

    case 3:
//      motores.motorSpeedE(88, FORWARD);
//      motores.motorSpeedD(83, FORWARD);
      motores.motorSpeedE(88, FORWARD);
      motores.motorSpeedD(85, FORWARD);
      break;

    case 4:
      motores.motorSpeedE(80, FORWARD);
      motores.motorSpeedD(150, FORWARD);
      break;

    case 5:
      motores.motorSpeedE(70, FORWARD);
      motores.motorSpeedD(200, FORWARD);
      break;

    case 6:
      motores.motorSpeedE(0, RELEASE);
      motores.motorSpeedD(0, RELEASE);


      if (sentido == true && passo == true) {
        serial.sendJson("car", "atM1");
        serialArduino.println("Mensagem enviada para M1 e esteira...");
        passo = false;
//        delay(250);
        serial.from = "0"; serial.state = "0";  
      }

      if (sentido == false && passo == false) {
        serial.sendJson("car", "atM2");
        serialArduino.println("Mensagem enviada para M2...");
        passo = true;
//        delay(250);
        serial.from = "0"; serial.state = "0";
      }
      break;

    case 7:
      motores.motorSpeedE(135, FORWARD);
      motores.motorSpeedD(135, BACKWARD);
      break;

    default:
      break;
  }
}

void verificaMensagem(String from, String state) {
  if (from == "M1" && state == "onCar" ) {
//    delay(100);
    sensores.estado = true;
    sentido = false;
  }
  if (from == "s2" && state == "nearM2") {
//    delay(100);
    sensores.estado = true;
    sentido = true;
  }
}
