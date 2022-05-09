#include "Wifi.h"
#include "webSocketClient.h"
#include "serial_comm.h"

WifiManager wifi;
Serial_comm serial;

//const String ip = "10.0.0.160"; //ip do Esp servidor (Esteira)
//const String ip = "ws://stem.local";
//const int port = 81; //porta do websocket no Esp servidor

//const String ip = "192.168.2.199"; //ip do Esp servidor (PC)
const String ip = "192.168.0.11"; //ip do Esp servidor (PC)
const int port = 1801; //porta do websocket no servidor

void setup() {
  Serial.begin(9600);
  delay(250);
  Serial.println("\nStarting Esp");

  //TO DO: enviar receivedType no websocket quando WS_CONNECT
  
  serial.doHandshake("ESP", "OK", "ARD");
  Serial.print("The type is: "); Serial.println(serial.receivedType);
  
  wifi.startWiFi();
  serial.sendJson("ESP_IP", wifi.ip);

  startWebSocketClient(ip, port);
  serial.sendJson("ws_client", "started");
  updateWebsocketClient();
  Serial.println("End of Setup");
};

void loop() {
  updateWebsocketClient();
  serial.getJson();
  if (serial.jsonUpdateCheck()){
    serial.serializeCurrentJson();
    sendMessageWsClient(serial.serializedCurrentJson);
  };
};
