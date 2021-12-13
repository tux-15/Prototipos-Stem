#include "Wifi.h"
#include "webSocketClient.h"
#include "webSocketServer.h"
#include "utils.h"

WifiManager wifi;

//const String ip = "10.0.0.119"; //ip do servidor principal
const String ip = "192.168.1.37";
const int port = 1801; //porta do websocket no servidor principal
//O webSocketServer abre na porta 81

void setup() {
  
  Serial.begin(9600);
  Serial.println("\n\r Starting");
  wifi.startWiFi();
  //wifi.startMDNS("stem");
  //startWebSocketClient(ip, port);
  startWebSocketServer();
  //updateWebsocketClient();
  updateWebSocketServer();
  Serial.println("End of Setup");
  
};

void loop() {

  //Any message sent by the server will be sent through Serial Communication.
  //updateWebsocketClient();
  updateWebSocketServer();
  
  char * messageFromSerial = getMessageFromSerial();

  if (messageFromSerial != "0"){
    sendMessageWsServer(messageFromSerial);
    Serial.println(messageFromSerial);
  };

  //wifi.updateMDNS();
};
