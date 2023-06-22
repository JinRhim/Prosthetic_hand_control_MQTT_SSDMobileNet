//ServoController.cpp
#include "ServoController.h"

ServoController::ServoController() {
  servos = new Servo[numServo]; // Dynamically allocate memory for servos
  isGrab = false;
}

void ServoController::attach(const uint8_t SERVO_PINS[]) {
  for (uint8_t i = 0; i < numServo; i++) {
    servos[i].attach(SERVO_PINS[i]);
  }
}

void ServoController::control(const uint8_t positions[]) {
  for (uint8_t i = 0; i < numServo; i++) {
    servos[i].write(positions[i]);
  }
}
