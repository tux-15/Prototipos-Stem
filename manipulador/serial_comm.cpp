#include "serial_comm.h"

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::setHandshakeInterval(long interval){
  this->interval = interval;
}

void Serial_comm::waitHandshake(){
  Serial.println("Blocking code until response from serial is received");
  
  while(this->espResponse != "typeOK"){
    unsigned long currentMillis = millis(); 
    if(currentMillis - previousMillis > this->interval) {
      this->previousMillis = currentMillis;
      this->sendJson("ARD", arduinoType); 
    };
    this->getJson();
    if(this->from == "ESP"){
      this->espResponse = this->state;
    }
  } //end of while
}

void Serial_comm::setArduinoType(String type){
  this->arduinoType = type;
}

String Serial_comm::getArduinoType(){
  return this->arduinoType;
}

void Serial_comm::sendJson(String from, String state){
  DynamicJsonDocument doc(128);
  doc["from"] = from;
  doc["state"] = state;
  serializeJson(doc, Serial); Serial.println();
};

void Serial_comm::getJson() {
  if (Serial.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, Serial);

    if (err == DeserializationError::Ok){
      
      this->from = doc["from"].as<String>();
      this->state = doc["state"].as<String>();
      
      Serial.print(this->from); Serial.print(" || ");
      Serial.println(this->state);
    }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (Serial.available() > 0)
        Serial.read();
    }
  }
};
