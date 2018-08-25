#ifndef IMESSAGEBROKER_H
#define IMESSAGEBROKER_H

#include <WiFi.h>;
#include "logging.h";
#include "settings.h";
#include "FP.h"

class IMessageBroker {
    public:    
        // pure virtual (abstract) method definitions
        virtual void init(FP<void,String>fp) = 0;
        virtual void loop() = 0;
        virtual void reconnect() = 0;
        virtual void publish(String message) = 0;
        virtual void sendmessage(const String cardId, const String product, const float price) = 0;
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

