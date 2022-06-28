#include "serial_comm.h"
#define serialESP Serial2
#define serialArduino Serial

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::setHandshakeInterval(long interval){
  this->interval = interval;
}

void Serial_comm::doHandshake(String origin, String hand, String destiny){
  serialArduino.println("Blocking code until type is received through serial");
  
  while(this->receivedType == ""){
    
    this->getJson();
    //serialArduino.println("Got here before crash");
    if(this->from == destiny){
      this->receivedType = this->state;
      this->sendJson(origin, hand);
      return;
    };
    yield();
  }; //end of while
}

void Serial_comm::waitHandshake(String origin, String hand, String destiny, String shake){
  serialArduino.println("Blocking code until response from serial is received");
  
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
  serializeJson(doc, serialESP); serialESP.println();
};

void Serial_comm::getJson() {
  if (serialESP.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, serialESP);

    if (err == DeserializationError::Ok){

      this->jsonUpdated = true;
      
      this->from = doc["from"].as<String>();
      this->state = doc["state"].as<String>();
      
      serialArduino.print(this->from); serialArduino.print(" || ");
      serialArduino.println(this->state);
    }
    else {
//      serialArduino.print("\ndeserializeJson() returned ");
//      serialArduino.println(err.c_str());
      while (serialESP.available() > 0){
        serialESP.read();
      };
    }
  }
};

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
  //serialArduino.print("Serialized Json is: "); serialArduino.println(this->serializedCurrentJson);
  return;
};
