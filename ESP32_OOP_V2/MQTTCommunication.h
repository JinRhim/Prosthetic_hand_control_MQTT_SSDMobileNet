#ifndef MQTT_COMMUNICATION_H
#define MQTT_COMMUNICATION_H
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "driver/gpio.h"

extern char* ssid;
extern char* password;
extern const char* mqtt_server;
extern const char* mqtt_topic;
extern String MQTT_MSG;


extern WiFiClient espClient;
extern PubSubClient client;

void MQTT_Init(); 
void setupWiFi();
void setupMQTT();
void callback(char* topic, byte* payload, unsigned int length);

#endif
