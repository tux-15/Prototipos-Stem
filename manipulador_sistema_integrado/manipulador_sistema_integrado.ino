#include "ServoControl.h"
#include "serial_comm.h"
#include "jointStates.h"

ServoControl servos;
Serial_comm serial;

bool checkMessage(String meta, String passo, int estado);

// {"meta":"E","passo":9,"estado":0}

void setup() {
  Serial.begin(9600);
  delay(250);
  servos.attachServos();
  servos.startPosition();
  Serial.println("End of setup");
  //servos.doTrajectory(originToPos1, originToPos1_size);
};

void loop() {
  serial.getJson();
  String meta = serial.docFromSerial["meta"].as<String>();
  String passo = serial.docFromSerial["passo"].as<String>();
  int estado = serial.docFromSerial["estado"].as<int>();

  if (checkMessage(meta, passo, estado)==true){
    servos.effector("open");
    servos.doTrajectory(zero_to_esteira, zero_to_esteira_size);
    delay(200); servos.effector("close"); delay(100);
    servos.doTrajectory(esteira_to_zero, esteira_to_zero_size);
    servos.doTrajectory(zero_to_carrinho, zero_to_carrinho_size);
    servos.effector("open"); delay(200);
    servos.doTrajectory(carrinho_to_zero, carrinho_to_zero_size);
    serial.sendJson("M2", "11", 1);
  };  
};

bool checkMessage(String meta, String passo, int estado) {
  if(meta == "E" && passo =="9" && estado == 1){
    serial.docFromSerial["estado"] = 0;
    serial.docFromSerial["passo"] = "0";
    serial.docFromSerial["meta"] = "0";
    return true;
  }
  else return false;
};
