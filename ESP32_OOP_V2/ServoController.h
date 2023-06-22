//ServoController.h
#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoController {
public:
  ServoController();
  bool isGrab; 
  const uint16_t Grab_Duration = 3000;
  const uint8_t numServo = 4;
  const uint8_t SERVO_PINS[4] = {13, 12, 14, 27};
  const uint8_t Release[4] = {100, 100, 100, 100};
  const uint8_t Grab[4] = {0, 0, 0, 0};
  void attach(const uint8_t SERVO_PINS[]);
  void control(const uint8_t positions[]);

private:
  Servo* servos; 
};

#endif
