#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Serial_comm{
  private:

  public:
    Serial_comm();
    ~Serial_comm();
    
    StaticJsonDocument<100> docFromSerial;
    
    void getJson();
    void sendJson(String meta, String passo, int estado);
};

#endif
