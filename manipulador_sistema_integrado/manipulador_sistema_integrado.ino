#include "ServoControl.h"
#include "serial_comm.h"
#include "jointStates.h"

ServoControl servos;
Serial_comm serial;

bool checkMessage(String meta, String passo, int estado);

// {"meta":"E","passo":9,"estado":1}
//{"meta":"value3","passo":9,"estado":90}

void setup() {
  Serial.begin(9600);
  delay(250);
  servos.attachServos();
  servos.setServoSpeed(50);
  delay(1000); 
  servos.startPosition();
  servos.effector("open");
  Serial.println("End of setup");
};

void loop() {
  serial.getJson();
  String meta = serial.docFromSerial["meta"].as<String>();
  const char *  meta2 = serial.docFromSerial["meta"].as<const char *>();
  String passo = serial.docFromSerial["passo"].as<String>();
  int estado = serial.docFromSerial["estado"].as<int>();

  if (checkMessage(meta, passo, estado)==true){
    //M2
    //servos.goTo(carrinho);
    servos.effector("open"); //delay(250);
    servos.goTo(origin); 
    servos.goTo(esteira); servos.effector("close"); delay(250);
    servos.goTo(origin); servos.goTo(carrinho); delay(250); 
    servos.effector("open"); delay(250); servos.goTo(carrinhoAux); delay(250);
    servos.goTo(origin); servos.effector("close");

    //M1
    serial.sendJson("M2", "11", 1);

//    servos.effector("open"); delay(500);
//    servos.goTo(carrinho); servos.effector("close"); delay(500);
//    servos.goTo(carrinhoAux); delay(250); servos.goTo(origin); delay(250);
//    servos.goTo(esteira); delay(250); servos.effector("open"); delay(500);
//    servos.goTo(origin);
    
    //M2
    //serial.sendJson("M1", "4", 1);
  };  
  servos.moveServo(meta2, estado);
};

bool checkMessage(String meta, String passo, int estado) {
  //M1
  //if(meta == "C" && passo =="4" && estado == 1){
  //M2
  if(meta == "C" && passo == "15" && estado ==1){ 
    serial.docFromSerial["estado"] = 0;
    serial.docFromSerial["passo"] = "0";
    serial.docFromSerial["meta"] = "0";
    return true;
  }
  else return false;
};
