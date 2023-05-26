#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include <ESP32Servo.h>
#include "esp_timer.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmap.h"
#include "servoControl.h"

#define OLED_RESET -1 
#define address_1 0x3D //display 2. change resistor location
#define address_2 0x3C  // display 1. 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//const char* ssid = "MICLab"; // your WiFi SSID
//const char* password = "miclabedu2021"; // your WiFi password

const char* ssid = "ICELab"; // your WiFi SSID
const char* password = "ICELab_Zhang"; // your WiFi password

const char* mqtt_server = "test.mosquitto.org"; // MQTT broker server
const char* mqtt_topic = "openmv/test"; // MQTT topic to subscribe to

WiFiClient espClient;
PubSubClient client(espClient);
servoControl servo; 

void disp_init() {
   if (!display1.begin(SSD1306_SWITCHCAPVCC, address_1)) {
    Serial.println(F("SSD1306 Display 1 allocation failed"));
    for (;;) {}  // Don't proceed, loop forever
  }
  
  if (!display2.begin(SSD1306_SWITCHCAPVCC, address_2)) {
    Serial.println(F("SSD1306 Display 2 allocation failed"));
    for (;;) {}  // Don't proceed, loop forever
  }

  display1.display();
  delay(300);
  display2.display();
  delay(300);
  display1.clearDisplay(); 
  display2.clearDisplay();
  display1.setTextSize(2); 
  display2.setTextSize(2);
  display1.setTextColor(SSD1306_WHITE); 
  display2.setTextColor(SSD1306_WHITE); 
  display1.setCursor(0,0);
  display2.setCursor(0,0);
  display1.println("Display 1");
  display1.println("Setup");
  display1.println("Finished");
  display2.println("Display 2");
  display1.println("Setup");
  display1.println("Finished");
  display1.display();
  display2.display();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  if (message == "Grab") {
    Serial.println("OpenMV requested Grab: Performing Grabbing Motion");
    display1.clearDisplay();
    display1.setTextSize(2);
    display1.setCursor(0,0);
    display1.setTextColor(SSD1306_WHITE);
    display1.println("OpenMV");
    display1.println("requested");
    display1.println("Grab");
    display1.display();
    servo.grab();
    delay(800);
  } 
  else if (message == "Release") {
    Serial.println("OpenMV requested Release: Performing Releasing Motion");
    servo.rest();
    display1.clearDisplay();
    display1.setTextSize(2);
    display1.setCursor(0,0);
    display1.setTextColor(SSD1306_WHITE);
    display1.println("OpenMV");
    display1.println("requested");
    display1.println("Release");
    display1.display();
  } 
  else {
    Serial.println("Unknown command received");
    display1.clearDisplay();
    display1.setTextSize(2);
    display1.setCursor(0,0);
    display1.setTextColor(SSD1306_WHITE);
    display1.println("Unknown");
    display1.println("Command");
    display1.println("MQTT Err");
    display1.display();
  }
}

void setup() {
  Serial.begin(115200);
  disp_init();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    display1.clearDisplay();
    display1.println("connecting to MQTT broker...."); 
    display1.display();
    if (client.connect("esp32")) {
      Serial.println("Connected to MQTT broker");
      display1.clearDisplay();
      display1.println("Connected to MQTT broker!!!"); 
      display1.display();
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      display1.clearDisplay();
      display1.println("Failed to connect:");
      display1.print(client.state()); 
      display1.display();
      delay(2000);
    }
  }

  
  servo.attachServos(); 
  display2.clearDisplay();
  display2.drawBitmap(0,0,custom_image, 128, 64, WHITE);
  display2.display();
  display1.println("End");
  display1.println("of");
  display1.println("setup");
  display1.display();
}

//debugging purpose
void test() {
  servo.grab(); 
  delay(2000);
  servo.rest();
  delay(2000);
}

// totally redundant code 
// fore resting state display 1. 
void resting_display() {
  static enum { DISPLAY_FIRST, DISPLAY_SECOND, DISPLAY_DONE } state = DISPLAY_FIRST;
  static unsigned long timer = 0;
  const unsigned long delayDuration = 300;
  static bool toggle = false; 
  static unsigned long toggleTimer = 0;
  

  switch (state) {
    case DISPLAY_FIRST:
      display1.clearDisplay();
      display1.setTextSize(2);
      display1.setCursor(0,0);
      display1.setTextColor(SSD1306_WHITE);
      display1.println("Waiting");
      display1.display();
      timer = millis();
      state = DISPLAY_SECOND;
      break;
    case DISPLAY_SECOND:
      if (millis() - timer >= delayDuration) {
        display1.println("MQTT"); 
        display1.println("Message..."); 
        display1.display();
        state = DISPLAY_DONE;
      }
      break;
    case DISPLAY_DONE:
      if (millis() - toggleTimer >= delayDuration) {
        toggle = !toggle;
        toggleTimer = millis();
        display1.clearDisplay();
        display1.setTextSize(2);
        display1.setCursor(0,0);
        display1.setTextColor(SSD1306_WHITE);
        display1.println("Waiting");
        display1.println("MQTT");
        display1.println("Message..."); 
        display1.println(String(toggle ? "..." : ""));
        display1.display();
      }
      break;
  }
}


void loop() {
  client.loop();
  resting_display(); 
  //test();
}
