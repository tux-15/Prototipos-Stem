#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <WebSocketsServer.h>   // Servidor interno para os protótipos interligados
#include "serial_comm.h"

void startWebSocketServer();
void webSocketServerEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);
void updateWebSocketServer();
void sendMessageWsServer(char * payload);

#endif
