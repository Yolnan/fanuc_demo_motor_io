#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;
uint8_t ledPin = 13;

void setIOCb(const std_msgs::Bool& setHigh) {
  if (setHigh.data == false) {
    digitalWrite(ledPin, LOW);  // sets the LED off 
  } else {
    digitalWrite(ledPin, HIGH); // sets the LED on
  }
}
ros::Subscriber<std_msgs::Bool> sub("/ee_motor_on", &setIOCb );

void setup() {
  pinMode(ledPin, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1000);

}
