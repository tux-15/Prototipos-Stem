#ifndef SERIAL_COMM_H_
#define SERIAL_COMM_H_

#include <ArduinoJson.h>
#include <Arduino.h>

class Serial_comm{
  private:

  public:
    Serial_comm();
    ~Serial_comm();
    
    StaticJsonDocument<100> docFromSerial;

    String from;
    String state;
    
    void getJson();
    void sendJson(String from, String state);
};

#endif
