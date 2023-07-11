// MQTTCommuncation.cpp file 
#include "MQTTCommunication.h"
#include "Display.h"
char* ssid = "ICELab"; // your WiFi SSID
char* password = "ICELab_Zhang"; // your WiFi password
const char* mqtt_server = "test.mosquitto.org"; // MQTT broker server
const char* mqtt_topic = "openmv/test"; // MQTT topic to subscribe to

WiFiClient espClient;
PubSubClient client(espClient);

String MQTT_MSG;

void MQTT_Init() {
  setupWiFi(); 
  setupMQTT(); 
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setupMQTT() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("esp32")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(100);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.println("running callback...");
  MQTT_MSG = ""; 
  for (int i = 0; i < length; i++) {
    MQTT_MSG += (char)payload[i];
    //strncpy(MQTT_MSG, payload);
  }
}
