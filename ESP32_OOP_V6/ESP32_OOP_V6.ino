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
#include "logistic_regression_classifier.h"
#include "driver/gpio.h"
#include "Display.h"
#include "EMGcontrol.h"
#include "bitmap.h"
#include <esp_now.h>

#define A0 0 
#define A1 1 
#define A2 2 
#define A3 3

EMGControl EMG;
ServoController servo;

Display disp1(&Wire, 0x3C); 
Display disp2(&Wire, 0x3D);
Display disp3(&Wire1, 0x3C); 
Display disp4(&Wire1, 0x3D);

uint16_t Emg_Threshold;  // POT input
uint16_t supine_emg_val;
uint16_t prone_emg_val;

uint8_t dist; 
uint8_t Dist_Threshold; // POT Input 
unsigned long current_time = 0; 
unsigned long previous_time_grab = 0; 
unsigned long previous_time_threshold = 0;


typedef enum {
    NEUTRAL = 0,
    GRAB = 1,
    RELEASE = 2
} EMG_Position;

EMG_Position current_emg_position; 

LogisticRegressionClassifier classifier; 

// Timer for grabbing delay
unsigned long last_grab = 0;


// automatic Interrupt Routine - callback function 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dist, incomingData, sizeof(dist));
}

void EMG_loop() {
  EMG.loop(A0); 
  EMG.loop(A1);
  //Serial.println("update status: " + String(EMG.isUpdate(A0)) +" " + String(EMG.isUpdate(A1)));
  if (EMG.isUpdate(A0) && EMG.isUpdate(A1)) {
    //Serial.println("EMG update");
    supine_emg_val = EMG.getVal(A0);
    prone_emg_val = EMG.getVal(A1);
    
    current_emg_position = static_cast<EMG_Position>(classifier.predict(supine_emg_val, prone_emg_val));
    //Serial.println(current_emg_position);
  }
}

void POT_Threshold_loop() {
  //Emg_Threshold = round(EMG.getThreshold(A3, 0, 4000) / 100.0) * 100;
  //Dist_Threshold = (EMG.getThreshold(A2, 0, 100)/10)*10;  
  current_time = millis(); 
  if (current_time - previous_time_threshold > 500) {
    Emg_Threshold = EMG.getThreshold(A3);   // 16 >> 6 --> 0 ~ 1024 
    Dist_Threshold = EMG.getThreshold(A2);   // 16 >> 8 --> 0 ~ 256
    previous_time_threshold = current_time; 
  }
}

void logic() {
  if (dist < Dist_Threshold) {
    current_time = millis();
    if (current_emg_position == GRAB) {
      servo.control(servo.Grab);
      disp3.drawBitMap(grab);
      delay(100);
      last_grab = millis(); 
    }
    else if (current_emg_position == RELEASE && (current_time - last_grab > 3000)) {
      servo.control(servo.Release);
      disp3.drawBitMap(release);
    }
    else {
      disp3.drawBitMap(neutral);
    }
  }
  else {
    disp3.drawBitMap(release);
    servo.control(servo.Release);
  }
}

void setText() {
  disp1.displayText("MQTTSignal\nPixel\nDistance:\n"  + String(dist), 2);
  disp2.displayText("SupineEMG:\n" + String(supine_emg_val) + "\nProne EMG:\n" + String(prone_emg_val), 2);
  disp4.displayText("EMG Cutoff\n" + String(Emg_Threshold) + "\nDistCutoff\n" + String(Dist_Threshold), 2);
}

void setup() {
  Serial.begin(115200);
  disp1.init();
  disp2.init();
  disp3.init();
  disp4.init();
  disp1.displayText("Setting\nSERVO", 2);
  disp2.displayText("Setting\nEMG", 2);
  disp3.displayText("Setting\nWIFI", 2);
  disp4.displayText("Setting\nMQTT", 2);
  //RF communication Logic 
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    disp4.displayText("Error\nInit\nESP-NOW", 2);
    return;
  } 
  servo.attach(servo.SERVO_PINS);
  disp2.displayText("SERVO\nDONE",2);
  EMG.setup(); 
  disp1.displayText("EMG setup\nDone!", 2);
  esp_now_register_recv_cb(OnDataRecv);
}

/*
Time for EMG_loop: 15709 us
Time for setText: 105808 us
Time for Threshold_loop: 15744 us

Time for Threshold_loop: 15711 us
Time for EMG_loop: 15698 us
Time for setText: 105745 us
*/

void loop() {
  // Measure time for Threshold_loop
  //start_time = micros();
  POT_Threshold_loop(); 
  //end_time = micros();
  //Serial.println("Time for Threshold_loop: " + String(end_time - start_time) + " us");

  // Measure time for EMG_loop
  //start_time = micros();
  EMG_loop(); 
  //end_time = micros();
  //Serial.println("Time for EMG_loop: " + String(end_time - start_time) + " us");

  logic();
  // Measure time for setText
  //start_time = micros();
  setText();
  //end_time = micros();
  //Serial.println("Time for setText: " + String(end_time - start_time) + " us");
}

