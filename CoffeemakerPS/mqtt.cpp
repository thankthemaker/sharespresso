#include "mqtt.h";

MqttService::MqttService() : espClient(), mqttClient(espClient) {
}

void MqttService::setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void MqttService::initMqtt(MQTT_CALLBACK_SIGNATURE) {
    this->mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    this->mqttClient.setCallback(callback);
}

void MqttService::loopMqtt() {
    if (!this->mqttClient.connected()) {
      this->mqttReconnect();
    }
    this->mqttClient.loop();
}

void MqttService::mqttReconnect() {
  // Loop until we're reconnected
  while (!this->mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (this->mqttClient.connect("Jura Giga X8", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      this->mqttClient.publish(MQTT_TOPIC_OUT, "Jura Giga X8 is ready now...");
      // ... and resubscribe
      this->mqttClient.subscribe(MQTT_TOPIC_IN);
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
  this->mqttClient.publish(MQTT_TOPIC_OUT, charBuf);
}

