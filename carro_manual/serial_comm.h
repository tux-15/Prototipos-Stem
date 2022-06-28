#ifndef SERIAL_COMM_H_
#define SERIAL_COMM_H_

#include <Arduino.h>
#include <ArduinoJson.h>

class Serial_comm{
  private:

    long previousMillis = 0; 
    long interval = 1000;  // (em milissegundos) -> define o tempo de "delay"
    String type = "0";
    String response = "0";
    String receivedType = "";
    
  public:
    Serial_comm();
    ~Serial_comm();
    
    StaticJsonDocument<100> docFromSerial;

    String from = "";
    String state = "";
    
    String serializedCurrentJson;

    bool jsonUpdated = false;
    
    void getJson();
    void sendJson(String from, String state);
    void serializeCurrentJson();
    bool jsonUpdateCheck();

    void setHandshakeInterval(long interval);
    void waitHandshake(String left, String hand, String right, String shake);
    void doHandshake(String origin, String hand, String destiny);
    
    void setType(String type);
    String getType();
    String getReceivedType();
};

#endif
