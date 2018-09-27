#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h";
#include <WiFi.h>;
#include <WiFiMulti.h>;
#include "settings.h"

class Wifi {  
    public:
        WiFiMulti wifiMulti;
        WiFiClient espClient;
        Wifi();
        void loop();
        void setup_wifi();
};
#endif

