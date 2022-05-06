#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <WebSocketsClient.h> 

void sendMessageWsClient(String payload);
void sendMessageWsClient(char * payload);

void webSocketClientEvent(WStype_t type, uint8_t * payload, size_t length);
void startWebSocketClient(String ip, int port);
void updateWebsocketClient();

#endif
