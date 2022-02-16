#include "utils.h"
#include "motores.h"
#include "sensores.h"

#define SerialESP Serial2

void verificaMensagem(String meta, String passo, int estado);
void girar180();

Serial_comm utils;
Motores motores;
Sensores sensores;

boolean sentido = true;

void setup() {
  SerialESP.begin(9600);
  SerialESP.println("Fim do setup");
  delay(5000);
  motores.motorSpeedE(88, FORWARD);
  motores.motorSpeedD(83, FORWARD);

}

void loop()
{
  //{"meta":"M2","passo":"11","estado":"1"}

  utils.getJson();
  String meta = utils.docFromSerial["meta"].as<String>();
  String passo = utils.docFromSerial["passo"].as<String>();
  int estado = utils.docFromSerial["estado"].as<int>();
  controle();
  verificaMensagem(meta, passo, estado);

}
void controle() {
  int retorno = sensores.readSensors();

  switch (retorno) {
    case 0:
      break;

    case 1:
//    motores.motorSpeedE(190, FORWARD);
      motores.motorSpeedD(83, FORWARD);
      break;

    case 2:
      motores.motorSpeedE(160, FORWARD);
      motores.motorSpeedD(83, FORWARD);
      break;

    case 3:
      motores.motorSpeedE(88, FORWARD);
      motores.motorSpeedD(83, FORWARD);

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
        utils.sendJson("C", "4", 1);
        delay(250);
      }

      if (sentido == false) {
        utils.sendJson("C", "15", 1);
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

void verificaMensagem(String meta, String passo, int estado) {
  if (meta == "M1" && passo == "4" && estado == 1) {

    delay(100);
    sensores.estado = true;
    sentido = false;
    utils.docFromSerial["estado"] = 0;
    utils.docFromSerial["passo"] = "0";
    utils.docFromSerial["meta"] = "0";
  }

  if (meta == "M2" && passo == "11" && estado == 1) {
    sensores.estado = true;
    sentido = true;
    utils.docFromSerial["estado"] = 0;
    utils.docFromSerial["passo"] = "0";
    utils.docFromSerial["meta"] = "0";
  }
}

void girar180() {
  motores.motorSpeedE(180, FORWARD);
  motores.motorSpeedD(180, BACKWARD);
  delay(1550);
}
