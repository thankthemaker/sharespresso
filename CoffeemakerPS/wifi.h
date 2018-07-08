#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h";
#include <ESP8266WiFi.h>;
#include "settings.h"

class Wifi {  
    public:
        WiFiClient espClient;
        Wifi();
        String setup_wifi();
};
#endif
