#include "utils.h"
#define SerialESP Serial2
//#define SerialESP Serial

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm(){};

void Serial_comm::sendJson(String meta, String passo, int estado){
  SerialESP.println("sending message");
  DynamicJsonDocument doc(128);
  doc["meta"] = meta;
  doc["passo"] = passo;
  doc["estado"] = estado;
  serializeJson(doc, SerialESP);
  SerialESP.println();
};

void Serial_comm::getJson() {
  if (SerialESP.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, SerialESP);

    if (err == DeserializationError::Ok){
      
      this->docFromSerial["meta"] = doc["meta"].as<String>();
      this->docFromSerial["passo"] = doc["passo"].as<String>();
      this->docFromSerial["estado"] = doc["estado"].as<int>();
      
      SerialESP.print(this->docFromSerial["meta"].as<String>()); SerialESP.print(" : ");
      SerialESP.print(this->docFromSerial["passo"].as<String>());SerialESP.print(" : ");
      SerialESP.println(this->docFromSerial["estado"].as<int>());
    }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (SerialESP.available() > 0)
        SerialESP.read();
    }
  }
};
