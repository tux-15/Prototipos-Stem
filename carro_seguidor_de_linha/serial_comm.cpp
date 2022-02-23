#include "serial_comm.h"
#define SerialESP Serial2
//#define SerialESP Serial

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::sendJson(String from, String state){
  SerialESP.println("sending message");
  DynamicJsonDocument doc(128);
  
  doc["from"] = from;
  doc["state"] = state;
  serializeJson(doc, SerialESP);
  SerialESP.println();
};

void Serial_comm::getJson() {
  if (SerialESP.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, SerialESP);

    if (err == DeserializationError::Ok){
      
      this->from = doc["from"].as<String>();
      this->state = doc["state"].as<String>();

      
      SerialESP.print(this->from); SerialESP.print(" : ");
      SerialESP.print(this->state);

    }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (SerialESP.available() > 0)
        SerialESP.read();
    }
  }
};
