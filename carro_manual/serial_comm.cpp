#include "serial_comm.h"
#define serialESP Serial2
#define SerialArduino Serial

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::sendJson(String from, String state){
  serialESP.println("sending message");
  DynamicJsonDocument doc(128);
  
  doc["from"] = from;
  doc["state"] = state;
  serializeJson(doc, serialESP);
  serialESP.println();
};

void Serial_comm::getJson() {
  if (serialESP.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, serialESP);

    if (err == DeserializationError::Ok){
      
      this->speed = doc["from"].as<int>();
      this->angle = doc["state"].as<int>();

      
//      SerialArduino.print(this->from); SerialArduino.print(" || ");
//      SerialArduino.println(this->state);

    }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (serialESP.available() > 0)
        serialESP.read();
    }
  }
};
