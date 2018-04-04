#ifndef CHUCKNORRIS_H
#define CHUCKNORRIS_H

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class Chucknorris {
    public:
        Chucknorris();
        String getNextChucknorrisFact();
};
#endif
