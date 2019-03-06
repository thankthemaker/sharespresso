#ifndef SETTINGS_H_
#define SETTINGS_H_

 #define OTA_UPDATE_URL      "http://www.thank-the-maker.org/ota/firmware.bin"

 // Your WiFi credentials.
 // Set password to "" for open networks.
#define WIFI_SSID            "***"
#define WIFI_PASSWORD        "***"
#define WIFI_SSID2           "***
#define WIFI_PASSWORD2       "***"
#define WIFI_SSID3           "***"
#define WIFI_PASSWORD3       "***"
 
 // MQTT settings
 #define MQTT_SERVER         "mqtt.thank-the-maker.org"
 #define MQTT_PORT           1883
 #define MQTT_USERNAME       "***"
 #define MQTT_PASSWORD       "***"  

 //AWS IOT config, change these:
 #define AWS_ENDPOINT        "***"
 #define AWS_KEY             "***"
 #define AWS_SECRET          "***"
 #define AWS_REGION          "eu-central-1"
 #define AWS_PORT            443

 #define TOPIC_IN            "/coffeemaker/gigax8/toCoffeemaker"
 #define TOPIC_OUT           "/coffeemaker/gigax8/fromCoffeemaker"
 #define TOPIC_COFFEE        "coffeemaker/coffee"

 #define APP_NAME            "Sharepresso"

 // Logging setings
 #define SERLOG              // logging to serial port

 // Syslog settings
 //#define SYSLOG
 #define SYSLOG_SERVER       "***"
 #define SYSLOG_PORT         514

//#define DEBUG // some more logging

// Choose coffeemaker
#define GIGAX8

 // Choose IoT-Device Sparkfun ESP32 or NodeMCU
 //#define NODEMCU_1_0
 #define SPARKFUN

 // Choose NFC-Reader Adafruit PN532 or RC522
 #define RC522

 // Choose display type OLED or TFT
 #define DISPLAY_OLED_SPI

//#define BROKER_MQTT
#define BROKER_AWS

//#define MULTI_WIFI

 // PIN definition Sparkfun ESP8266 Thing Dev
 #ifdef SPARKFUN
  #define DEVICE_HOSTNAME     "Sparkfun ESP32 Thing Dev"
  #define EEPROM_SIZE_BYTES   4096
  // number of cards, max is (4096-11*2)/6=679 on ESP32 Sparkfun Thing Dev
  #define MAX_CARDS           80  // only 100 cards to keep some space reserved  
  // offset for pricelist 4096-11*2=4074 on ESP32 Sparkfun Thing Dev
  #define PRICELIST_ADDRESS_OFFSET     4073

  #define BUZPIN              21
  #define OLED_SDA_PIN        35
  #define OLED_SCL_PIN        36
  #define TFT_LED             1 //TX
  #define TFT_CS              21
  #define TFT_RST             22 
  #define TFT_DC              23
  #define TFT_SCLK            24  
  #define TFT_MOSI            25 
  #define BLE_RX_PIN          26
  #define BLE_TX_PIN          27
  #define JURA_RX_PIN         16
  #define JURA_TX_PIN         17 

 //#ifdef PN532
  #define PN532_SS            (2)
  #define PN532_SCK           (14)
  #define PN532_MISO          (12)
  #define PN532_MOSI          (13)
//#endif
//#ifdef RC522
  #define RC522_SS             2
  #define RC522_RST            0
//#endif
  #define SD_CARD_CS          14

  #define BLE_ENABLED         0
 #endif

 // PIN definition AI Thinker NodeMCU 1.0 
 #ifdef NODEMCU_1_0
  #define DEVICE_HOSTNAME     "NodeMCU 1.0 Amica"
  #define EEPROM_SIZE_BYTES   4096
  // number of cards, max is (4096-11*2)/6=679 on NodeMCU v1.0
  #define MAX_CARDS           80  // only 100 cards to keep some space reserved  
  // offset for pricelist 4096-11*2=4074 on NodeMCU v1.0
  #define PRICELIST_ADDRESS_OFFSET     4073

  #define BUZPIN              3 // RX
  #define OLED_SDA_PIN        D2
  #define OLED_SCL_PIN        D1
  #define TFT_LED             1 //TX
  #define TFT_CS              D1
  #define TFT_RST             D2  
  #define TFT_DC              D0
  #define TFT_SCLK            D5   
  #define TFT_MOSI            D7  
#ifdef BLE_ENABLED
  #define BLE_RX_PIN          3
  #define BLE_TX_PIN          1
#endif
  #define JURA_RX_PIN         D4  //RX
  #define JURA_TX_PIN         D3  //TX

//#ifdef PN532
  #define PN532_SCK            D5
  #define PN532_MISO           D6
  #define PN532_MOSI           D7
  #define PN532_SS             D0
//#endif
//#ifdef RC522
  #define RC522_SS             9  //SD2
  #define RC522_RST            10 //SD3
//#endif

  #define SD_CARD_CS          D8

  #define BLE_ENABLED         0
 #endif
#endif




