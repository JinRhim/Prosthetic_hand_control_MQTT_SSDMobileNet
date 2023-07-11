/************************
 *  Jin Chul, Rhim 
 *  Summmer 2023 
 *  SFSU Senior Engineering Project 
 *  ESP32 Pin 13,12,14,27 should be connected to Servo PWM Line 
 ************************/
 
#include <Arduino.h>
#include <WiFi.h>
#include <String.h>
#include <PubSubClient.h>
#include "ServoController.h"
#include "MQTTCommunication.h"
#include "driver/gpio.h"
#include "Display.h"
#include "EMGcontrol.h"

EMGControl EMG; 
ServoController servo;
Display disp1(0x3D); 
Display disp2(0x3C);

uint16_t emg_val; 
uint8_t dist; 
unsigned long current_time = 0; 
unsigned long previous_time = 0; 

void MQTT_MSG_Check() {
  client.loop(); 
  dist = MQTT_MSG.toInt();
  if (dist < 50 && !servo.isGrab) {
    servo.isGrab = true; 
    //Serial.println("Grabbing");
    disp1.displayText("Grab\n...", 2); 
    servo.control(servo.Grab); 
  }
  else { 
    current_time = millis(); 
    if (current_time - previous_time > 3000) {
      if (dist > 70 && servo.isGrab) {
        servo.isGrab = false; 
        //Serial.println("Releasing");
        disp1.displayText("Release\n...",2);
        servo.control(servo.Release); 
      }
      previous_time = current_time; 
    }
  }
}

void EMG_loop() {
  EMG.loop(); 
  emg_val = EMG.getVal(); 
  if (emg_val != 0) { 
    disp2.displayText("EMG Val:\n" + String(emg_val), 2);
  } 
}

void setup() {
  Serial.begin(115200);
  disp1.init();
  disp2.init();
  disp1.displayText("Setting\nWIFI", 2);
  MQTT_Init();
  //Serial.println("MQTT done");
  servo.attach(servo.SERVO_PINS);
  disp2.displayText("SERVO\nDONE",2);
  EMG.setup(); 
  disp1.displayText("Setup()\nDone!", 2);
  disp2.displayText("Setup()\nDone!", 2);
}

void loop() {
  MQTT_MSG_Check(); 
  EMG.loop(); 
}
