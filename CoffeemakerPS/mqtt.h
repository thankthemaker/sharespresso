#include "Arduino.h";
#include <PubSubClient.h>;
#include <ESP8266WiFi.h>;

#ifndef SETTINGS_H_
 #include "settings.h"
#endif

#define MQTT_CALLBACK_SIGNATURE std::function<void(char*, uint8_t*, unsigned int)> callback

class MqttService {
    private:
      WiFiClient espClient;
      PubSubClient mqttClient;
  
    public:
        MqttService();
        
        void setup_wifi();

        void initMqtt(MQTT_CALLBACK_SIGNATURE);
        void loopMqtt();
        void mqttReconnect();
        void publish(String message);
};

