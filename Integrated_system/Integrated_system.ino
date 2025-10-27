
// works with MKR1010

#include <SPI.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"
#include <utility/wifi_drv.h>  // library to drive to RGB LED on the MKR1010
#include "DHT.h"               // Library to temperature and humidity sensor

#define DHTPIN 1  // DHT22 connected to pin 1
#define DHTTYPE DHT22
#define SWITCH_PIN 2 //switch connected to pin 2

DHT dht(DHTPIN, DHTTYPE);

/*
**** please enter your sensitive data in the Secret tab/arduino_secrets.h
**** using format below
#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";
 */
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
//const char* ssid1         = SECRET_SSID1;
//const char* password1     = SECRET_PASS1;
const char* mqtt_username = SECRET_MQTTUSER;
const char* mqtt_password = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1884;

// create wifi object and mqtt object
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Make sure to update your lightid value below with the one you have been allocated
String lightId = "18";  // the topic id number or user number being used.

// Here we define the MQTT topic we will be publishing data to
String mqtt_topic = "student/CASA0014/luminaire/" + lightId;
String clientId = "";  // will set once i have mac address so that it is unique

// NeoPixel Configuration - we need to know this to know how to send messages
// to vespera
const int num_leds = 72;
const int payload_size = num_leds * 3;  // x3 for RGB

// Create the byte array to send in MQTT payload this stores all the colours
// in memory so that they can be accessed in for example the rainbow function
byte RGBpayload[payload_size];

void setup() {
  Serial.begin(115200);
  //while (!Serial); // Wait for serial port to connect (useful for debugging)
  Serial.println("Vespera");


  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);

  Serial.print("This device is Vespera ");
  Serial.println(lightId);

  // Connect to WiFi
  startWifi();

  // Connect to MQTT broker
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setBufferSize(2000);
  mqttClient.setCallback(callback);

  Serial.println("Set-up complete");

  dht.begin();  // Initiate the DHT22 sensor

  pinMode(SWITCH_PIN, INPUT_PULLUP);
}


void loop() {
  // Reconnect if necessary
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }

  if (WiFi.status() != WL_CONNECTED) {
    startWifi();
  }
  // keep mqtt alive
  mqttClient.loop();

  bool isNightMode = digitalRead(SWITCH_PIN) == LOW; //ON=LOW, OFF=HIGH


  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate >= 200) {
    float temp = dht.readTemperature();  //Read the DHT22 datas every 0.2 seconds

    if (isnan(temp)) {
      Serial.println("Failed to read from DHT22 sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.println(temp);

      int r, g, b;
      temperatureToRGB(temp, r, g, b);  //Temperature variations are mapped to spectral changes

      if (isNightMode) {
        
        float brightnessFactor = 0.2;  // lightness drop to 20%
        r = int(r * brightnessFactor);
        g = int(g * brightnessFactor);
        b = int(b * brightnessFactor);
        Serial.println("Night mode ON (dimmed)");
      }


      for (int pixel = 0; pixel < num_leds; pixel++) {
        RGBpayload[pixel * 3 + 0] = (byte)r;
        RGBpayload[pixel * 3 + 1] = (byte)g;
        RGBpayload[pixel * 3 + 2] = (byte)b;
      }

      mqttClient.publish(mqtt_topic.c_str(), RGBpayload, payload_size);

      Serial.print("Published color RGB(");
      Serial.print(r);
      Serial.print(", ");
      Serial.print(g);
      Serial.print(", ");
      Serial.print(b);
      Serial.println(")");
    }

    lastUpdate = now;
  }
}

// Function to update the R, G, B values of a single LED pixel
// RGB can a value between 0-254, pixel is 0-71 for a 72 neopixel strip
void send_RGB_to_pixel(int r, int g, int b, int pixel) {
  // Check if the mqttClient is connected before publishing
  if (mqttClient.connected()) {
    // Update the byte array with the specified RGB color pattern
    RGBpayload[pixel * 3 + 0] = (byte)r;  // Red
    RGBpayload[pixel * 3 + 1] = (byte)g;  // Green
    RGBpayload[pixel * 3 + 2] = (byte)b;  // Blue

    // Publish the byte array
    mqttClient.publish(mqtt_topic.c_str(), RGBpayload, payload_size);

    Serial.println("Published whole byte array after updating a single pixel.");
  } else {
    Serial.println("MQTT mqttClient not connected, cannot publish from *send_RGB_to_pixel*.");
    reconnectMQTT();
  }
}

void send_all_off() {
  // Check if the mqttClient is connected before publishing
  if (mqttClient.connected()) {
    // Fill the byte array with the specified RGB color pattern
    for (int pixel = 0; pixel < num_leds; pixel++) {
      RGBpayload[pixel * 3 + 0] = (byte)0;  // Red
      RGBpayload[pixel * 3 + 1] = (byte)0;  // Green
      RGBpayload[pixel * 3 + 2] = (byte)0;  // Blue
    }
    // Publish the byte array
    mqttClient.publish(mqtt_topic.c_str(), RGBpayload, payload_size);

    Serial.println("Published an all zero (off) byte array.");
  } else {
    Serial.println("MQTT mqttClient not connected, cannot publish from *send_all_off*.");
  }
}

void send_all_random() {
  // Check if the mqttClient is connected before publishing
  if (mqttClient.connected()) {
    // Fill the byte array with the specified RGB color pattern
    for (int pixel = 0; pixel < num_leds; pixel++) {
      RGBpayload[pixel * 3 + 0] = (byte)random(50, 256);  // Red - 256 is exclusive, so it goes up to 255
      RGBpayload[pixel * 3 + 1] = (byte)random(50, 256);  // Green
      RGBpayload[pixel * 3 + 2] = (byte)random(50, 256);  // Blue
    }
    // Publish the byte array
    mqttClient.publish(mqtt_topic.c_str(), RGBpayload, payload_size);

    Serial.println("Published an all random byte array.");
  } else {
    Serial.println("MQTT mqttClient not connected, cannot publish from *send_all_random*.");
  }
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}

void temperatureToRGB(float temp, int& r, int& g, int& b) {

  if (temp < 21) temp = 21;
  if (temp > 41) temp = 41;  // Restricted temperature range

  float ratio = (temp - 21.0) / 20.0;
  // Normalise the temperature to obtain a ratio representing the position of the temperature within the RGB interval.

  if (ratio < 0.1667) {
    // Purple to Blue
    r = int(255 * (ratio / 0.1667));  //0-255
    g = 0;
    b = 255;
  } else if (ratio < 0.3333) {
    // Blue to Azure
    r = 0;
    g = int(255 * ((ratio - 0.1667) / 0.1667));  // 0-255
    b = 255;
  } else if (ratio < 0.5) {
    // Azure to Green
    r = 0;
    g = 255;
    b = int(255 - 255 * ((ratio - 0.3333) / 0.1667));
  } else if (ratio < 0.6667) {
    // Green to Yellow
    r = int(255 * ((ratio - 0.5) / 0.1667));
    g = 255;
    b = 0;
  } else if (ratio < 0.8333) {
    // Yellow to orange
    r = 255;
    g = int(255 - 128 * ((ratio - 0.6667) / 0.1667));
    b = 0;
  } else {
    // Orange to Red
    r = 255;
    g = int(127 - 127 * ((ratio - 0.8333) / 0.1667));
    b = 0;
  }
}
