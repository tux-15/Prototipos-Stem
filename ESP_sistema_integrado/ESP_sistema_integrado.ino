#include "Wifi.h"
#include "webSocketClient.h"
#include "utils.h"

WifiManager wifi;
const String ip = "10.0.0.161"; //ip do Esp servidor
//const String ip = "ws://stem.local";
const int port = 81; //porta do websocket no Esp servidor

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting Esp");
  wifi.startWiFi();
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
