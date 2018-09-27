#ifndef CHUCKNORRIS_H
#define CHUCKNORRIS_H

#include <WiFi.h>
#ifdef ESP8266
  #include <ESP8266HTTPClient.h>
#else
  #include <HTTPClient.h>
#endif
#include <ArduinoJson.h>

class Chucknorris {
    public:
        Chucknorris();
        String getNextChucknorrisFact();
};
#endif

