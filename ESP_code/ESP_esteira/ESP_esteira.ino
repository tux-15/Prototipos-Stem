#include "Wifi.h"
#include "webSocketClient.h"
#include "webSocketServer.h"
#include "utils.h"
#include "serial_comm.h"

WifiManager wifi;
Serial_comm serial;

const String ip = "10.0.0.119"; //ip do servidor principal (Raspberry)
const int port = 1801; //porta do websocket no servidor principal 

//O webSocketServer abre na porta 81  --> onde os outros ESPs se conectam

void setup() {
  Serial.begin(9600);
  delay(250);
  Serial.println("\n\r Starting");

  wifi.startWiFi();
  //wifi.startMDNS("stem");

  delay(100);
  
  serial.sendJson("ESP_IP", wifi.ip);
  startWebSocketClient(ip, port);
  startWebSocketServer();
  
  delay(150);
  
  updateWebsocketClient();
  updateWebSocketServer();
  Serial.println("End of Setup");
};

void loop() {

  //Any message sent by the server will be sent through Serial Communication.
  updateWebsocketClient();
  updateWebSocketServer();
  
  serial.getJson();
  if (serial.jsonUpdateCheck()){
    serial.serializeCurrentJson();
    sendMessageWsServer(serial.serializedCurrentJson);
    sendMessageWsClient(serial.serializedCurrentJson);
  };
  //wifi.updateMDNS();
};
