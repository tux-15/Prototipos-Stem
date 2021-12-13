#include "ServoControl.h"
#include "serial_comm.h"
#include "jointStates.h"

ServoControl servos;
Serial_comm serial;

bool checkMessage();

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

  if (checkMessage()==true){
    
    delay(500);
    
    Serial.println("picking up object and opening effector");
    servos.effector("open");
    delay(250);
    servos.doTrajectory(originToPos1, originToPos1_size);
    delay(250);
    Serial.println("closing effector and moving to destination");
    servos.effector("close");
    delay(250);
    servos.doTrajectory(pos1ToPos2, pos1ToPos2_size);
    delay(500);
    servos.effector("open");
    delay(500);
    
    Serial.println("back to origin");
    servos.doTrajectory(pos2ToOrigin, pos2ToOrigin_size);
    servos.effector("close");
    serial.sendJson("M2", "11", 1);
  };  
};

bool checkMessage() {
  if(serial.docFromSerial["meta"].as<String>() == "E" && serial.docFromSerial["passo"].as<String>() == "9" && serial.docFromSerial["estado"].as<int>() == 1){
    serial.docFromSerial["estado"] = 0;
    return true;
  }
  else return false;
};
