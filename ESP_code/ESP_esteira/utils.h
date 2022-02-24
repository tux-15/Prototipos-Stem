#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

void recvWithStartEndMarkers();
char * getMessageFromSerial();
void setNewData(boolean state);

#endif
