// Your WiFi credentials.
// Set password to "" for open networks.
#define SETTINGS_H_

#define MAX_CARDS           40  // number of cards, max is (1024-11*2)/6=167 on Arduino Uno

#define WIFI_SSID           "<YOUR_SSID>"
#define WIFI_PASSWORD       "<YOUR_PASSWD>"

#define MQTT_SERVER         "<YOUR_MQTT_SERVER>"
#define MQTT_PORT           1833
#define MQTT_TOPIC_IN       "coffeemaker/gigax8/in"
#define MQTT_TOPIC_OUT      "coffeemaker/gigax8/out"
#define MQTT_USERNAME       "<YOUR_MQTT_USERNAME>"
#define MQTT_PASSWORD       "<YOUR_MQTT_PASSWORD>"