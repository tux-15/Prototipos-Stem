#include "utils.h"

const byte numChars = 64;
char receivedChars[numChars];

boolean newDataFromArduino = false;
long previousMillis = 0; 
long interval =100;  // (em milissegundos) -> define o tempo de "delay"


char * getMessageFromSerial() {
  
  recvWithStartEndMarkers();
  unsigned long currentMillis = millis(); 
  if(currentMillis - previousMillis > interval) {
    
    if(newDataFromArduino == true){
      setNewData(false);     
      previousMillis = currentMillis;
      return receivedChars;
//      Serial.print("Received from Arduino: ");
//      Serial.println(receivedChars);
    };
    previousMillis = currentMillis;
  };
  return "0";
};

void setNewData(boolean state){
  newDataFromArduino = state;
};

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '{';
    char endMarker = '}';
    char rc;
 
    while (Serial.available() > 0 && newDataFromArduino == false){
        rc = Serial.read();
        if (recvInProgress == true){
            if (rc != endMarker){
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars){
                    ndx = numChars - 1;
                };
            }
            else{
                receivedChars[ndx] = endMarker;
                ndx++;
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newDataFromArduino = true;
            }
        }
        else if (rc == startMarker){
            recvInProgress = true;
            receivedChars[ndx] = rc;
            ndx++;
        }
    }
};
