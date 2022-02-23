#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <WebSocketsClient.h>  
#include "serial_comm.h"

//void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

void sendMessageWsClient(String payload);
void sendMessageWsClient(uint8_t * payload);

void webSocketClientEvent(WStype_t type, uint8_t * payload, size_t length);
void startWebSocketClient(String ip, int port);
void updateWebsocketClient();
    
#endif
