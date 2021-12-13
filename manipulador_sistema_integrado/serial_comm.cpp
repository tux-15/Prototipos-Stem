#include "serial_comm.h"

Serial_comm::Serial_comm() {
    this->docEstatico["meta"]="M2";
    this->docEstatico["passo"]="11";
    this->docEstatico["estado"]="1";
};

Serial_comm::~Serial_comm(){};

void Serial_comm::sendJson(String meta, String passo, int estado){
  DynamicJsonDocument doc(512);
  doc["meta"] = meta;
  doc["passo"] = passo;
  doc["estado"] = estado;
  serializeJson(doc, Serial);
};

void Serial_comm::getJson() {
  if (Serial.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, Serial);

    if (err == DeserializationError::Ok){
      
      this->docFromSerial["meta"] = doc["meta"].as<String>();
      this->docFromSerial["passo"] = doc["passo"].as<String>();
      this->docFromSerial["estado"] = doc["estado"].as<int>();
      
      Serial.println(this->docFromSerial["meta"].as<String>());
      Serial.println(this->docFromSerial["passo"].as<String>());
      Serial.println(this->docFromSerial["estado"].as<int>());
    }
    else {
//      Serial.print("\ndeserializeJson() returned ");
//      Serial.println(err.c_str());
      while (Serial.available() > 0)
        Serial.read();
    }
  }
};
