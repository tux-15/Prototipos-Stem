#include "motores.h"


#define serialArduino Serial
#define serialESP Serial2

Motores motores;

void setup() {
  // put your setup code here, to run once:
  serialESP.begin(9600);
  serialArduino.begin(9600);

  serialArduino.println("start code...");
}

void loop() {
  // put your main code here, to run repeatedly:
  motores.controle();
}
