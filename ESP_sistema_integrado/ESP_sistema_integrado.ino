#include "Wifi.h"
#include "webSocketClient.h"
#include "utils.h"
#include "serial_comm.h"

WifiManager wifi;
<<<<<<< HEAD
//const String ip = "10.0.0.161"; //ip do Esp servidor
const String ip = "192.168.1.38";
=======
Serial_comm serial;
const String ip = "10.0.0.161"; //ip do Esp servidor
>>>>>>> 8a19712a5f11de80df5114194661bb3895fd8304
//const String ip = "ws://stem.local";
const int port = 81; //porta do websocket no Esp servidor

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting Esp");
  wifi.startWiFi();
  serial.sendJson("ESP_IP", wifi.ip, 1),  
  startWebSocketClient(ip, port);
  updateWebsocketClient();
  Serial.println("End of Setup");
};

void loop() {
  updateWebsocketClient();
  
  char * messageFromSerial = getMessageFromSerial();
  
  if (messageFromSerial != "0"){
    Serial.println(messageFromSerial);
    sendMessageWsClient(messageFromSerial);
  };
};
