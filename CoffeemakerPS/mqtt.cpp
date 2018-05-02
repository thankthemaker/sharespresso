#include "mqtt.h";

MqttService::MqttService() : espClient(), mqttClient(espClient) {}

void MqttService::init(MQTT_CALLBACK_SIGNATURE) {
    this->mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    this->mqttClient.setCallback(callback);
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
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (this->mqttClient.connect("Jura Giga X8", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      this->mqttClient.publish(TOPIC_OUT, "Jura Giga X8 is ready now...");
      // ... and resubscribe
      this->mqttClient.subscribe(TOPIC_IN);
    } else {
      Serial.print("failed, rc=");
      Serial.print(this->mqttClient.state());
      Serial.println(" try again in 5 seconds");
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

void MqttService::sendmessage(const String cardId, const String product, const int price) {
  this->publish(cardId + ";" + product + ";" + price);  
}



