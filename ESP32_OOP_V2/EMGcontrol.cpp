#include "EMGControl.h"


EMGControl::EMGControl() {
  uint16_t last_time = 0;
  uint32_t current_time = 0 ;
  uint8_t num_readings = 0;
  uint16_t adc_readings[ARRAY_SIZE];
  uint16_t curr_average_pooling = 0;
  uint16_t prev_average_pooling = 0;
  bool is_update = false; 
}

int EMGControl::delay_rate(int num) {
  float delayValue; 
  switch (num) {
  case RATE_ADS1115_8SPS:
    // Set the delay for 8 samples per second
    delayValue = 1000 / 8;
    break;
  case RATE_ADS1115_16SPS:
    // Set the delay for 16 samples per second
    delayValue = 1000 / 16;
    break;
  case RATE_ADS1115_32SPS:
    // Set the delay for 32 samples per second
    delayValue = 1000 / 32;
    break;
  case RATE_ADS1115_64SPS:
    // Set the delay for 64 samples per second
    delayValue = 1000 / 64;
    break;
  case RATE_ADS1115_128SPS:
    // Set the delay for 128 samples per second
    delayValue = 1000 / 128;
    break;
  case RATE_ADS1115_250SPS:
    // Set the delay for 250 samples per second
    delayValue = 1000 / 250;
    break;
  case RATE_ADS1115_475SPS:
    // Set the delay for 475 samples per second
    delayValue = 1000 / 475;
    break;
  case RATE_ADS1115_860SPS:
    // Set the delay for 860 samples per second
    delayValue = 1000 / 860;
    break;
  default:
    // Handle any other sample rate values not accounted for
    // Set a default delay value or perform appropriate action
    delayValue = 0;
    break;
  }
  return delayValue;
}

uint16_t EMGControl::zero_centering(uint16_t array[], uint8_t size) {
  uint32_t total = 0;  // Use a larger type to avoid overflow

  // Calculate the average of the array
  for (int i = 0; i < size; i++) {
    total += array[i];
  }
  uint16_t average = total / size;

  uint32_t average_pooling = 0;
  // Subtract the average from each element (zero centering)
  for (int i = 0; i < size; i++) {
    array[i] = abs(average - array[i]);
    average_pooling += array[i];
  }
  return average_pooling / size;
}

void EMGControl::setup(void) {
  ads.setGain(GAIN_TWO);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  ads.setDataRate(RATE_ADS1115_860SPS);

  delay_time = delay_rate(ads.getDataRate());
}

void EMGControl::loop(void) {
  current_time = millis();
  // If 2ms have passed since the last reading
  if (current_time - last_time >= delay_time) {
    uint16_t adc0 = ads.readADC_SingleEnded(0);
    adc_readings[num_readings] = adc0;
    num_readings++;

    if (num_readings == ARRAY_SIZE) {
      is_update = true; 
      curr_average_pooling = zero_centering(adc_readings, ARRAY_SIZE);
      num_readings = 0;

      uint16_t diff = abs(curr_average_pooling - prev_average_pooling);
      prev_average_pooling = curr_average_pooling;
    }

    last_time = current_time;
  }
}

uint16_t EMGControl::getVal(void) {
  if (is_update) {
    is_update = false; 
    return this->curr_average_pooling;
  }
  else {
    return 0; 
  }
}




