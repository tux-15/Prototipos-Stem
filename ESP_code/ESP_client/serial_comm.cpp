#include "serial_comm.h"

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::setHandshakeInterval(long interval){
  this->interval = interval;
}

void Serial_comm::doHandshake(String origin, String hand, String destiny){
  Serial.println("Blocking code until type is received through serial");
  
  while(this->receivedType == ""){
    this->getJson();
    //Serial.println("Got here before crash");
    if(this->from == destiny){
      this->receivedType = this->state;
      this->sendJson(origin, hand);
      return;
    };
    yield();
  }; //end of while
}

void Serial_comm::waitHandshake(String origin, String hand, String destiny, String shake){
  Serial.println("Blocking code until response from serial is received");
  
  while(this->response != shake){
    unsigned long currentMillis = millis(); 
    
    if(currentMillis - this->previousMillis > this->interval){
      this->previousMillis = currentMillis;
      this->sendJson(origin, hand);
    };
    
    this->getJson();
    
    if(this->from == destiny){
      this->response = this->state;        
    };
    yield();
  } //end of while
}

void Serial_comm::setType(String type){
  this->type = type;
}

String Serial_comm::getType(){
  return this->type;
}

String Serial_comm::getReceivedType(){
  return this->receivedType;
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

      this->jsonUpdated = true;
      
      this->from = doc["from"].as<String>();
      this->state = doc["state"].as<String>();
          }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (Serial.available() > 0){
        Serial.read();
      };
    }
  }
};

void Serial_comm::printCurrentJson(){
  Serial.print("from-> ");Serial.print(this->from);
  Serial.print(" / state-> ");Serial.println(this->state);
}

bool Serial_comm::jsonUpdateCheck(){
  if(this->jsonUpdated == true){
    this->jsonUpdated = false;
    return true;
  } else return false;
};

void Serial_comm::serializeCurrentJson(){
  this->serializedCurrentJson = "";
  DynamicJsonDocument doc(64);
  doc["from"] = this->from;
  doc["state"] = this->state;
  serializeJson(doc, this->serializedCurrentJson);
  //Serial.print("Serialized Json is: "); Serial.println(this->serializedCurrentJson);
  return;
};
