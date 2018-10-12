#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h";
#ifdef ESP32
#include <WiFi.h>;
#include <WiFiMulti.h>;
#else
#include <ESP8266WiFi.h>;
#include <ESP8266WiFiMulti.h>;
#endif
#include "settings.h"

class Wifi {  
    public:
#ifdef ESP32
        WiFiMulti wifiMulti;
#else
        ESP8266WiFiMulti wifiMulti;
#endif
        WiFiClient espClient;
          
        Wifi();
        void loop();
        void setup_wifi();
};
#endif

