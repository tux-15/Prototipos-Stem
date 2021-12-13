#include "Wifi.h"
#include "webSocketClient.h"
#include "webSocketServer.h"
#include "utils.h"
#include "serial_comm.h"

WifiManager wifi;

<<<<<<< HEAD
//const String ip = "10.0.0.119"; //ip do servidor principal
const String ip = "192.168.1.37";
=======
Serial_comm serial;

const String ip = "10.0.0.119"; //ip do servidor principal
>>>>>>> 8a19712a5f11de80df5114194661bb3895fd8304
const int port = 1801; //porta do websocket no servidor principal
//O webSocketServer abre na porta 81

void setup() {
  
  Serial.begin(9600);
  Serial.println("\n\r Starting");
  
  wifi.startWiFi();
  //wifi.startMDNS("stem");
<<<<<<< HEAD
  //startWebSocketClient(ip, port);
  startWebSocketServer();
  //updateWebsocketClient();
=======
  serial.sendJson("ESP_IP", wifi.ip, 1),  
  
  startWebSocketClient(ip, port);
  startWebSocketServer();
  
  updateWebsocketClient();
>>>>>>> 8a19712a5f11de80df5114194661bb3895fd8304
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
