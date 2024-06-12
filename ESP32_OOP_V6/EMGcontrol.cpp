#include "EMGControl.h"



/*

#define ADS1X15_REG_CONFIG_PGA_MASK (0x0E00)   ///< PGA Mask
#define ADS1X15_REG_CONFIG_PGA_6_144V (0x0000) ///< +/-6.144V range = Gain 2/3
#define ADS1X15_REG_CONFIG_PGA_4_096V (0x0200) ///< +/-4.096V range = Gain 1
#define ADS1X15_REG_CONFIG_PGA_2_048V (0x0400) ///< +/-2.048V range = Gain 2 (default)

*/

EMGControl::EMGControl() {
  current_time = 0;
  is_update = 0; // store bitwise logic 

  for (int i = 0; i < 2; i++) {
    num_readings[i] = 0;
    last_time[i] = 0;
    curr_average_pooling[i] = 0;
    prev_average_pooling[i] = 0;
    for (int j = 0; j < ARRAY_SIZE; j++) {
      adc_readings[i][j] = 0;
    }
  }
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
  ads.setGain(GAIN_ONE); // +- 4.096V 

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  ads.setDataRate(RATE_ADS1115_860SPS);

  delay_time = delay_rate(ads.getDataRate());
}

void EMGControl::loop(int port) {
  current_time = millis();
  // If 2ms have passed since the last reading
  if (current_time - last_time[port] >= delay_time) {
    //Serial.print("Port: " + String(port) + " updated");
    uint16_t adc_raw = ads.readADC_SingleEnded(port);
    adc_readings[port][num_readings[port]] = adc_raw;
    num_readings[port]++;
    
    if (num_readings[port] == ARRAY_SIZE) {
      is_update |= (1 << port);    // for example, A0 update --> 0x0000.0001
      //Serial.print("port: " + String(port) +  " is_update: ");
      //Serial.println(is_update, BIN);
      num_readings[port] = 0;
      curr_average_pooling[port] = zero_centering(adc_readings[port], ARRAY_SIZE);
      prev_average_pooling[port] = curr_average_pooling[port];
    }
    last_time[port] = current_time;
  }
}

uint16_t EMGControl::getVal(int port) {
  // this works correctly....
  //Serial.print("is_update: "); Serial.println(is_update); 
  //Serial.println(this->curr_average_pooling);
  is_update &= ~(1 << port);  // turn off, A0 update --> 0x????.???0 set to is_update as false
  return this->curr_average_pooling[port];
}

uint16_t EMGControl::getThreshold(int port) {
  // Map the threshold_reading from the range 25,000 to 0-2000
  //Serial.print("Threshold: "); Serial.println(this->threshold_reading);
  // the last dangling number force update. Remove 3 LSB digit. 0 ~ 32768 to 0 ~ 4096
  //threshold_reading = ads.readADC_SingleEnded(port) >> 3;
  //uint16_t mapped_val = map(this->threshold_reading, 0, 4096, min, max);
  return (ads.readADC_SingleEnded(port) >> 6);
}

bool EMGControl::isUpdate(int port) {
  return ((is_update &(1<<port)) != 0);
}




