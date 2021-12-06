#include "webSocketServer.h"

WebSocketsServer webSocketServer(81); // Servidor WebSocket na porta 81

void startWebSocketServer() { // Inicializa o webSocket
  webSocketServer.begin();
  webSocketServer.onEvent(webSocketServerEvent);          // função de callback para eventos que acontecerem no webSocket
  Serial.println("WebSocket server started.");
};

void updateWebSocketServer(){
  webSocketServer.loop();
};

void sendMessageWsServer(char * payload){
    webSocketServer.broadcastTXT(payload);
};

void webSocketServerEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  
  switch(type) {    
    case WStype_DISCONNECTED: 
      Serial.printf("\rServer Disconnected!\n");
      break;
    
    case WStype_CONNECTED: {
      IPAddress ip = webSocketServer.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n\r", num, ip[0], ip[1], ip[2], ip[3], payload);
    };
      break;
      
    case WStype_TEXT:
      Serial.printf("%s\n\r", payload);
      webSocketServer.broadcastTXT(payload);
      //sendMessageWsServer(payload);
      //Serial.println();
      break;
      
    case WStype_BIN:
      hexdump(payload, length);
      //sendMessageWsServer(payload);
      webSocketServer.broadcastTXT(payload);
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
