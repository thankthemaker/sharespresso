#ifdef ESP8266
#ifndef AWSIOT_H_
#define AWSIOT_H_

#include <Arduino.h>
#include <Stream.h>
#include <WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//AWS
#include "sha256.h"
#include "Utils.h"

//WEBSockets
#include "Hash.h" // lokale Lib beim Umstieg auf ESP32
#include <WebSocketsClient.h>

//MQTT PAHO
#include <SPI.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

//AWS MQTT Websocket
#include "Client.h"
#include "AWSWebSocketClient.h"
#include "CircularByteBuffer.h"
#include <ArduinoJson.h>

#include "settings.h"
#include "IMessageBroker.h"
#include "ntpClient.h"

const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 2;

class AwsIotClient : public IMessageBroker {
  private:
    AWSWebSocketClient awsWSclient;
    IPStack ipstack;
    MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers> *client = NULL;
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
