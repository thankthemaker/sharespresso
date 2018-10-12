#include "IMessageBroker.h"

#if defined(BROKER_MQTT)
 #include "mqtt.h";
#elif defined(BROKER_AWS)
#ifdef ESP32
 #include "awsIot1.h"
#else
 #include "awsIot.h"
#endif
#endif

MessageBrokerFactory* MessageBrokerFactory::instance = 0;

MessageBrokerFactory::MessageBrokerFactory() {}

MessageBrokerFactory* MessageBrokerFactory::getInstance() {
    if (instance == 0){
        instance = new MessageBrokerFactory();
    }

    return instance;
}

IMessageBroker* MessageBrokerFactory::createMessageBroker() {
#if defined(BROKER_MQTT)
 return new MqttService();
#elif defined(BROKER_AWS)
 return new AwsIotClient();
#endif
}

