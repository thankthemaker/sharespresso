#ifdef ESP32
#ifndef AWSIOT_H_
#define AWSIOT_H_

#include <Arduino.h>
#include <Stream.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <AWS_IOT.h>
#include <ArduinoJson.h>

#include "settings.h"
#include "IMessageBroker.h"
#include "NtpClient.h"

const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 2;

class AwsIotClient : public IMessageBroker {
  private:
    AWS_IOT awsIot;
    void publish_to_topic(const char* topic, const String& message);
    //# of connections
    long connection = 0;
    //count messages arrived
    int arrivedcount = 0;

  public:
    AwsIotClient();
    void init(FP<void,String>fp);
    void loop();
    void reconnect();
    char* generateClientID ();
    bool connect ();
    void publish(String message);
    void subscribe ();
    void sendmessage(const String cardId, const String product, const float price); 
};
#endif
#endif