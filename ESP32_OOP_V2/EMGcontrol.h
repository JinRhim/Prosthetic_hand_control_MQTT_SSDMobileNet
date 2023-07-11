#ifndef EMG_CONTROL_H
#define EMG_CONTROL_H

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

// does this violate oop 
// ask zhenyu 
#define ARRAY_SIZE 20 

class EMGControl {
public:
  EMGControl();
  void setup();
  void loop();
  uint16_t getVal();

private:
  Adafruit_ADS1115 ads;
  uint32_t last_time;
  uint32_t current_time;
  uint8_t num_readings;
  uint16_t adc_readings[ARRAY_SIZE];
  uint16_t curr_average_pooling;
  uint16_t prev_average_pooling;
  float delay_time;
  bool is_update; 

  int delay_rate(int num);
  uint16_t zero_centering(uint16_t array[], uint8_t size);
};

#endif
