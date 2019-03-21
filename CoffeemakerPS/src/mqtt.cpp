#include "mqtt.h";

static FP<void,String> fp;

// On ESP822 platform this method has to stay in main sketch. This is because of
// callback signature "std::function<void(char*, uint8_t*, unsigned int)> callback"
// in PubSubClient for ESP8266
void callbackMqtt(char* topic, byte* payload, unsigned int length) {
//  logger.log("Message arrived [" + String(topic) + "] ");
  String command  = "";
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
//  logger.log("cmd via mqtt:" + command);
  fp(command);
}

MqttService::MqttService() : espClient(), mqttClient(espClient) {}

void MqttService::init(FP<void,String>tmpFp) {
    this->mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    this->mqttClient.setCallback(callbackMqtt);
    fp = tmpFp;
}

void MqttService::loop() {
    if (!this->mqttClient.connected()) {
      this->reconnect();
    }
    this->mqttClient.loop();
}

void MqttService::reconnect() {
  // Loop until we're reconnected
  while (!this->mqttClient.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    if (this->mqttClient.connect("Jura Giga X8", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println(F("connected"));
      // Once connected, publish an announcement...
      this->mqttClient.publish(TOPIC_OUT, "Jura Giga X8 is ready now...");
      // ... and resubscribe
      this->mqttClient.subscribe(TOPIC_IN);
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(this->mqttClient.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MqttService::publish(String message) {
  char charBuf[message.length()+1];
  message.toCharArray(charBuf, message.length()+1); 
  this->mqttClient.publish(TOPIC_OUT, charBuf);
}

void MqttService::sendmessage(const String cardId, const String product, const float price) {
  this->publish(cardId + ";" + product + ";" + price);  
}

void MqttService::sendmessage(const String cardId, const int credit) {
  this->publish(cardId + ";" + credit);  
}
