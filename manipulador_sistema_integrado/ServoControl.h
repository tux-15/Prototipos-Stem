#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_


#include <VarSpeedServo.h> 
#include <Arduino.h>

class ServoControl{
  private:
    VarSpeedServo servo1;
    VarSpeedServo servo2;
    VarSpeedServo servo3;
    VarSpeedServo servo4;
    VarSpeedServo servo5;
    VarSpeedServo servos[4] = {servo1, servo2, servo3, servo4};
    
    int servoSpeed = 0;
    
  public:
    ServoControl();
    ~ServoControl();
    void attachServos();
    void startPosition();
    void effector(String state);

    void setServoSpeed(int servoSpeed);
    void goTo(const float trajetoria[4]);
    void moveServo(const char * servo, int angle);
};

#endif
