#ifndef EMG_CONTROL_H
#define EMG_CONTROL_H

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

#define ARRAY_SIZE 10 

class EMGControl {
public:
  EMGControl();
  void setup();
  void loop(int port);
  uint16_t getVal(int port);
  uint16_t getThreshold(int port);
  bool isUpdate(int port);

private:
  Adafruit_ADS1115 ads;
  uint32_t last_time[2]; 
  uint32_t current_time;
  uint8_t num_readings[2];
  uint16_t adc_readings[2][ARRAY_SIZE];
  uint16_t curr_average_pooling[2];
  uint16_t prev_average_pooling[2];
  float delay_time;
  uint8_t is_update; //instead of 4 array of bool, use this bitwise operation
  uint16_t threshold_reading;

  int delay_rate(int num);
  uint16_t zero_centering(uint16_t array[], uint8_t size);
};

#endif
