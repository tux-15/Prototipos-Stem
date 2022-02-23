#include "serial_comm.h"

Serial_comm::Serial_comm() {};

Serial_comm::~Serial_comm() {};

void Serial_comm::getJson()
{
  if (Serial.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, Serial);

    if (err == DeserializationError::Ok)
    {
      this->from = doc["from"].as<String>();
      this->state = doc["state"].as<String>();
      
//      this->sendJson(this->from, this->state);
      
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

void Serial_comm::sendJson(String from, String state)
{
  DynamicJsonDocument doc(512);
  doc["from"] = from;
  doc["state"] = state;

  serializeJson(doc, Serial);
  Serial.println();
};
