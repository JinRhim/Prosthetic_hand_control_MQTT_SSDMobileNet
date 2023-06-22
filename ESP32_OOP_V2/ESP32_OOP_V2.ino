/************************
 *  Jin Chul, Rhim 
 *  Summmer 2023 
 *  SFSU Senior Engineering Project 
 *  ESP32 Pin 13,12,14,27 should be connected to Servo PWM Line 
 ************************/
 
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "ServoController.h"
#include "MQTTCommunication.h"
#include "driver/gpio.h"

ServoController servo;
uint8_t dist; 

unsigned long current_time = 0; 
unsigned long previous_time = 0; 

void MQTT_MSG_Check() {
  client.loop(); 
  dist = MQTT_MSG.toInt();
  if (dist < 50 && !servo.isGrab) {
    servo.isGrab = true; 
    Serial.println("Grabbing");
    servo.control(servo.Grab); 
  }
  else { 
    current_time = millis(); 
    if (current_time - previous_time > 3000) {
      if (dist > 70 && servo.isGrab) {
        servo.isGrab = false; 
        Serial.println("Releasing");
        servo.control(servo.Release); 
      }
      previous_time = current_time; 
    }
  }
}


void setup() {
  Serial.begin(115200);
  MQTT_Init();
  Serial.println("MQTT done");
  servo.attach(servo.SERVO_PINS);
  Serial.println("Servo done");
}

void loop() {
  MQTT_MSG_Check(); 
}
