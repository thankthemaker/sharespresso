#define SETTINGS_H_

// number of cards, max is (1024-11*2)/6=167 on Arduino Uno
#define MAX_CARDS           40  

// Your WiFi credentials.
// Set password to "" for open networks.
#define WIFI_SSID           "<YOUR_WIFI_SSID>"
#define WIFI_PASSWORD       "<YOUR_WIFI_PASSWORD>"

// MQTT settings
#define MQTT_SERVER         "<YOUR_MQTT_SERVER>"
#define MQTT_PORT           1883
#define MQTT_TOPIC_IN       "coffeemaker/gigax8/in"
#define MQTT_TOPIC_OUT      "coffeemaker/gigax8/out"
#define MQTT_USERNAME       "<YOUR_MQTT_USERNAME>"
#define MQTT_PASSWORD       "<YOUR_MQTT_PASSWORD>"  

// Default PIN definition
#define BUZPIN              0
#define OLED_SDA_PIN        4
#define OLED_SDC_PIN        5
#define BLE_RX_PIN          7
#define BLE_TX_PIN          8
#define JURA_RX_PIN         15
#define JURA_TX_PIN         16 

#define PN532_SS            (2)
#define PN532_SCK           (14)
#define PN532_MISO          (12)
#define PN532_MOSI          (13)
