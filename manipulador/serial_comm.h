#ifndef SERIAL_COMM_H_
#define SERIAL_COMM_H_

#include <ArduinoJson.h>
#include <Arduino.h>



class Serial_comm{
  private:
  
    long previousMillis = 0; 
    long interval = 1000;  // (em milissegundos) -> define o tempo de "delay"
    String arduinoType = "0";
    String espResponse = "0";

  public:
    Serial_comm();
    ~Serial_comm();
    
    StaticJsonDocument<100> docFromSerial;

    String from;
    String state;
    
    void getJson();
    void sendJson(String from, String state);

    void setHandshakeInterval(long interval);
    void waitHandshake();
    void setArduinoType(String type);
    String getArduinoType();
};

#endif
