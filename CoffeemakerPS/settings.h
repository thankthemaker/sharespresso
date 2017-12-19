// Your WiFi credentials.
// Set password to "" for open networks.
#define SETTINGS_H_

#define MAX_CARDS           40  // number of cards, max is (1024-11*2)/6=167 on Arduino Uno

#define WIFI_SSID           "***REMOVED***"
#define WIFI_PASSWORD       "***REMOVED***"

#define MQTT_SERVER         "mqtt.thank-the-maker.org"
#define MQTT_PORT           1833
#define MQTT_TOPIC_IN       "coffeemaker/gigax8/in"
#define MQTT_TOPIC_OUT      "coffeemaker/gigax8/out"
#define MQTT_USERNAME       "dgey"
#define MQTT_PASSWORD       "test"