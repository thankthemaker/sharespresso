#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h";
#include <ESP8266WiFi.h>;
#include "settings.h"

class Wifi {  
    public:
        WiFiClient espClient;
        Wifi();
        void setup_wifi();
};
#endif
