#include "ServoControl.h"
#include "serial_comm.h"
#include "jointStates.h"

ServoControl servos;
Serial_comm serial;

//long previousMillis = 0; 
//long interval = 1000;  // (em milissegundos) -> define o tempo de "delay"
 
//{"from":"s1","state":"nearM1"}

void setup() {
  
  Serial.begin(9600);
  delay(250);
  
  serial.setHandshakeInterval(1000);
  serial.setType("manipulador");
  
  serial.waitHandshake("ARD", serial.getType(), "ESP", "OK");

  //=========================================================
  
  servos.attachServos();
  servos.setServoSpeed(45);
  servos.setEffectorAngles(80, 150);
  servos.startPosition();
  servos.effector("open");
  
  Serial.println("End of setup");
};

void loop() {  
  serial.getJson();
  if (serial.jsonUpdateCheck()){
    serial.printCurrentJson();
    serial.serializeCurrentJson();
    servos.moveServo(serial.from, serial.state);
  };
  //serial.from = "0"; serial.state = "0";
};

//  unsigned long currentMillis = millis(); 
//
//  if(currentMillis - previousMillis > interval) {
//      previousMillis = currentMillis;
//      Serial.println("{\"from\": \"coming\", \"state\": \"from Arduino\"}");
//  };

  //access values by using serial.from and serial.state

//  if (serial.from == "s1" && serial.state == "nearM1"){
//    Serial.println("Picking up object from conveyor belt");
//    servos.goTo(esteira); servos.effector("close"); delay(1000); 
//    servos.goTo(origin); servos.goTo(carrinhoAux); servos.goTo(carrinho); servos.effector("open"); delay(500);
//    servos.goTo(carrinhoAux); servos.goTo(origin);
//    Serial.println("Object placed on line-follower");
//    serial.sendJson("M1", "onCar");
//    serial.from = "0"; serial.state = "0";
//  }
//
//  if (serial.from == "car" && serial.state == "atM2"){
////    Serial.println("Picking up object from line-follower");
////    servos.goTo(carrinhoAux); servos.goTo(carrinho); servos.effector("close"); delay(1000); 
////    servos.goTo(carrinhoAux); servos.goTo(origin); servos.goTo(esteira);
////    servos.effector("open"); delay(500);
////    servos.goTo(origin);
////    serial.sendJson("M2", "onS2");
////    Serial.println("Object placed on conveyor belt");
//    serial.from = "0"; serial.state = "0";
//  }
//};
