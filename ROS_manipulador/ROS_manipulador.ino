#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
#include <Servo.h>

ros::NodeHandle nh;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//Servo servo5;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

void joint_cb();

void joint_cb(const sensor_msgs::JointState& cmd_msg){

  int pos1 = cmd_msg.position[0] * (180/PI);
  int pos2 = cmd_msg.position[1] * (180/PI);
  int pos3 = cmd_msg.position[2] * (180/PI);
  int pos4 = cmd_msg.position[3] * (180/PI);
//  int pos5 = cmd_msg.position[4] * (180/PI);

  str_msg.data = "Banana";
  chatter.publish( &str_msg );

  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  //servo5.write(pos5);
}

ros::Subscriber<sensor_msgs::JointState> sub("joint_states", joint_cb);

void setup() {

  Serial.begin(9600);
  Serial.println("Oi");
  
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
 
  //servo5.attach(12);

  nh.getHardware()-> setBaud(115200);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

}

void loop() {

  nh.spinOnce();
  delay(1);
}
