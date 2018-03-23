#ifndef SETTINGS_H_
#define SETTINGS_H_

 #define OTA_UPDATE_URL      "http://www.thank-the-maker.org/ota/firmware.bin"

 // Your WiFi credentials.
 // Set password to "" for open networks.
 #define WIFI_SSID           "***REMOVED***"
 #define WIFI_PASSWORD       "***REMOVED***"
 //#define WIFI_SSID           "3***REMOVED***"
 //#define WIFI_PASSWORD       "***REMOVED***"

 // MQTT settings
 #define MQTT_SERVER         "mqtt.thank-the-maker.org"
 #define MQTT_PORT           1883
 #define MQTT_TOPIC_IN       "/coffeemaker/gigax8/toCoffeemaker"
 #define MQTT_TOPIC_OUT      "/coffeemaker/gigax8/fromCoffeemaker"
 #define MQTT_USERNAME       "dgey"
 #define MQTT_PASSWORD       "test"  

 //AWS IOT config, change these:
 #define AWS_ENDPOINT        "***REMOVED***"
 #define AWS_KEY             "AKIAJSN4NKYKS5FEQZ6Q"
 #define AWS_SECRET          "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"
 #define AWS_REGION          "us-west-2"
 #define AWS_TOPIC           "coffeemaker/coffee"
 #define AWS_PORT            443

 #define APP_NAME            "Sharepresso"

 // Logging setings
 #define SERLOG              // logging to serial port

 // Syslog settings
 //#define SYSLOG
 #define SYSLOG_SERVER       "genas.fritz.box"
 #define SYSLOG_PORT         514

#define JOURNAL

//#define DEBUG // some more logging

// Choose coffeemaker
#define GIGAX8
//#define X7
//#define S95

 // Choose IoT-Device Sparkfun or NodeMCU
 #define NODEMCU_1_0
 //#define SPARKFUN

 // Choose NFC-Reader Adafruit PN532 or RC522
 //#define PN532
 #define RC522

 // Choose display type OLED or TFT
 //#define DISPLAY_OLED
 #define DISPLAY_TFT

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
  #define OLED_SCL_PIN        5
  #define BLE_RX_PIN          7
  #define BLE_TX_PIN          8
  #define JURA_RX_PIN         15
  #define JURA_TX_PIN         16 

  #define PN532_SS            (2)
  #define PN532_SCK           (14)
  #define PN532_MISO          (12)
  #define PN532_MOSI          (13)

  #define SD_CARD_CS          xx

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

  #define BUZPIN              3 // RX
  #define OLED_SDA_PIN        D2
  #define OLED_SCL_PIN        D1
  #define TFT_LED             1 //TX
  #define TFT_CS              D1
  #define TFT_RST             D2  
  #define TFT_DC              D3
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


