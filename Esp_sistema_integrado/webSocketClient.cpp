#include "webSocketClient.h"

WebSocketsClient webSocketClient;

void updateWebsocketClient(){
  webSocketClient.loop();
};

void startWebSocketClient(String ip, int port) { // Inicializa o webSocket
  
  webSocketClient.begin(ip, port, "/");
  webSocketClient.onEvent(webSocketClientEvent);  
  Serial.println("WebSocket client started.");
};

void sendMessageWsClient(String payload){
    webSocketClient.sendTXT(payload);
};

void webSocketClientEvent(WStype_t type, uint8_t * payload, size_t length) {
  
  switch(type) {    
    case WStype_DISCONNECTED: 
      Serial.printf("\n\rClient Disconnected!\n");
      break;
    
    case WStype_CONNECTED: 
      Serial.printf("\rConnected to url: %s\n\r", payload);

      // send message to server when Connected
      webSocketClient.sendTXT("{\"start\": \"ESP_on\"}");
      break;
      
    case WStype_TEXT:
      Serial.printf("%s", payload);
      Serial.println();

      break;
    case WStype_BIN:
      hexdump(payload, length);
      Serial.println();
      break;
        
    case WStype_PING:
      // pong will be send automatically
      //Serial.printf("\r[WSc] get ping\n\r");
      break;
      
    case WStype_PONG:
      // answer to a ping we send
      //Serial.printf("\r[WSc] get pong\n");
      break;       
  };
};
