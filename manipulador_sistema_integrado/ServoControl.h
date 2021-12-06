#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_


#include <Servo.h>
#include <Arduino.h>

class ServoControl{
  private:
    Servo servo1;
    Servo servo2;
    Servo servo3;
    Servo servo4;
    Servo servo5;
    Servo servos[4] = {servo1, servo2, servo3, servo4};
    
  public:
    ServoControl();
    ~ServoControl();
    void attachServos();
    void startPosition();
    void effector(String state);

    void doTrajectory(const float trajetoria[][4], int sizeOfTrajectory);
};

#endif
