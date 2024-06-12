//ServoController.cpp
#include "ServoController.h"

ServoController::ServoController() {
  servos = new Servo[numServo]; // Dynamically allocate memory for servos
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

void ServoController::slow_grab() {
  control(Release);
  const uint8_t increment = 2; // The amount by which we increment servo positions
  const uint16_t delayTime = 1; // Delay in milliseconds between each increment

  // Starting from release position, move towards grab position
  for (uint8_t i = Release[0]; i >= Grab[0]; i -= increment) {
    // Update the position of all servos with the current i value
    for (uint8_t j = 0; j < numServo; j++) {
      servos[j].write(i);
    }
    delay(1);
  }
  Serial.println("End of slow grab");
}
