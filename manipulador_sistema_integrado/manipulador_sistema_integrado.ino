#include "ServoControl.h"
#include "serial_comm.h"
#include "jointStates.h"

ServoControl servos;
Serial_comm serial;

// 
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

  //access values by using serial.from and serial.state

  if (serial.from == "c" && serial.state == "atM1"){
    Serial.println("doing m1 thing");
    serial.from = "0"; serial.state = "0";
  }

  if (serial.from == "c" && serial.state == "atM2"){
    Serial.println("doing m2 thing");
    serial.from = "0"; serial.state = "0";
  }

  //servos.moveServo(meta2, estado);
};
