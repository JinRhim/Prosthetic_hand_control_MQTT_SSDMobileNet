#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include "driver/gpio.h"
#include <ESP32Servo.h>


class servoControl
{
private:
  Servo myservo_thumb;  // create servo object to control a servo
  Servo myservo_index; 
  Servo myservo_pinky;
public:
  void attachServos();
  void grab();
  void rest();
  void pinch();
  void half_clench();
};

#endif
