#ifndef IMESSAGEBROKER_H
#define IMESSAGEBROKER_H

#include <ESP8266WiFi.h>;
#include <MQTTClient.h>
#include "logging.h";
#include "settings.h";

 #define MQTT_CALLBACK_SIGNATURE std::function<void(char*, uint8_t*, unsigned int)> callback

class IMessageBroker {
    public:    
        // pure virtual (abstract) method definitions
        virtual void init(MQTT_CALLBACK_SIGNATURE) = 0;
        virtual void loop() = 0;
        virtual void reconnect() = 0;
        virtual void publish(String message) = 0;
        virtual void sendmessage(const String cardId, const String product, const int price) = 0;

};

class MessageBrokerFactory {
    public:
        static MessageBrokerFactory* getInstance();
        IMessageBroker* createMessageBroker();

    private:
        MessageBrokerFactory();    
        static MessageBrokerFactory *instance;    
};
#endif
