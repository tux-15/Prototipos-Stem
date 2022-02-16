#include "utils.h"

Utils::Utils() {
};

Utils::~Utils() {};

void Utils::getJson()
{
  if (Serial.available() > 2) {
    StaticJsonDocument<100> doc;
    DeserializationError err = deserializeJson(doc, Serial);

    if (err == DeserializationError::Ok)
    {
      this->meta = doc["meta"].as<String>();
      this->passo = doc["passo"].as<int>();
      this->estado = doc["estado"].as<String>();
      Serial.println(this->meta);
      Serial.println(this->passo);
      Serial.println(this->estado);
    }
    else {
      Serial.print("\ndeserializeJson() returned ");
      Serial.println(err.c_str());
      while (Serial.available() > 0)
        Serial.read();
    }
  }
};

void Utils::setJson(String meta, int passo, int estado)
{
  DynamicJsonDocument doc(512);
  doc["meta"] = meta;
  doc["passo"] = passo;
  doc["estado"] = estado;

  serializeJson(doc, Serial);
  Serial.println();
};
