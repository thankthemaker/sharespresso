#define SETTINGS_H_

#define OTA_UPDATE_URL      "http://www.thank-the-maker.org/ota/firmware.bin"

// Your WiFi credentials.
// Set password to "" for open networks.
#define WIFI_SSID           "<YOUR_WIFI_SSID>"
#define WIFI_PASSWORD       "<YOUR_WIFI_PASSWORD>"

// MQTT settings
#define MQTT_SERVER         "mqtt.thank-the-maker.org"
#define MQTT_PORT           1883
#define MQTT_TOPIC_IN       "/coffeemaker/gigax8/toCoffeemaker"
#define MQTT_TOPIC_OUT      "/coffeemaker/gigax8/fromCoffeemaker"
#define MQTT_USERNAME       "<YOUR_MQTT_USERNAME>"
#define MQTT_PASSWORD       "<YOUR_MQTT_PASSWORD>"  


#define APP_NAME            "Sharepresso"

// Logging setings
#define SERLOG              1 // logging to serial port

// Syslog settings
#define SYSLOG              0
#define SYSLOG_SERVER       "genas.fritz.box"
#define SYSLOG_PORT         514

#define NODEMCU_1_0
//#define SPARKFUN

// PIN definition Sparkfun ESP8266 Thing Dev
#ifdef SPARKFUN
 #define DEVICE_HOSTNAME     "Sparkfun ESP8266 Thing Dev"
 #define EEPROM_SIZE_BYTES   512
 // number of cards, max is (512-11*2)/6=81 on ESP8266 Sparkfun Thing Dev
 #define MAX_CARDS           40  // only 60 cards to keep some space reserved  
 // offset for pricelist 512-11*2=490 on ESP8266 Sparkfun Thing Dev
 #define PRICELIST_ADDRESS_OFFSET     489

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

 #define BLE_ENABLED         1
#endif

// PIN definition AI Thinker NodeMCU 1.0
#ifdef NODEMCU_1_0
  #define DEVICE_HOSTNAME     "NodeMCU 1.0 Amica"
  #define EEPROM_SIZE_BYTES   4096
  // number of cards, max is (4096-11*2)/6=679 on NodeMCU v1.0
  #define MAX_CARDS           40  // only 40 cards to keep some space reserved  
  // offset for pricelist 512-11*2=490 on ESP8266 Sparkfun Thing Dev
  #define PRICELIST_ADDRESS_OFFSET     4073

  #define BUZPIN              0  //D3
  #define OLED_SDA_PIN        4  //D2
  #define OLED_SDC_PIN        5  //D1
  #define BLE_RX_PIN          3  //RX
  #define BLE_TX_PIN          1  //TX
  #define JURA_RX_PIN         9  // SD2
  #define JURA_TX_PIN         10 // SD3

 #define PN532_SCK            (14) //D5
 #define PN532_MISO           (12) //D6
 #define PN532_MOSI           (13) //D7
 #define PN532_SS             (15) //D8

 #define BLE_ENABLED         0
#endif