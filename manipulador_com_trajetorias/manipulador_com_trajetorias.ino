#include <Servo.h>
#include "trajetorias.h"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

Servo servos[] = {servo1, servo2, servo3, servo4};

void startPosition();

int size = 1;

void setup() {
  Serial.begin(9600);
  delay(250);

  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  servo5.attach(8);

  startPosition();
  delay(2000);
  doTrajectory(OriginToPOS1, OriginToPOS1_size);
  delay(2500);
}

void loop() {

  doTrajectory(POS1toPOS2, POS1toPOS2_size);
  delay(2500);
  doTrajectory(POS2toPOS1, POS2toPOS1_size);
  //startPosition();
  delay(2500);

}

void doTrajectory(float trajetoria[][4], int sizeOfTrajectory) {
  for (int i = 0; i < sizeOfTrajectory; i++) {
    Serial.println();
    for (int j = 0; j < 4; j++) {
      servos[j].write(trajetoria[i][j]);
      Serial.println(trajetoria[i][j]);
    }
  }
};

void startPosition() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);

};
