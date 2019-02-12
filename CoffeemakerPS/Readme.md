# First steps

Meanwhile several hardware setups are supported. You'll have to choose the hardware components you want to use in the settings.h file. We support ESP8266 and ESP32 plattforms and have tested our code with "Sparkfun ESP32 Thing" and "NodeMCU v1.0 Amica (ESP8266)". We tested small 0.96 inch OLED (I2C), 1.3 inch OLED (SPI) and 1.8 inch TFT (SPI) displays. We also support different types of NFC cardreader. MFRC522 and PN532 based should work.

## Edit settings.h
Please take a look at the settings.h file in the project. Here you have all parameters in a single place and you have to a adjust 
some parameters, e.g. the SSID and credential for your WiFi and the settings for the MQTT connection to make the sketch work as 
expected. 

## Import needed Libraries
Depending on the hardware and features you choose in settings.h, you'll need different libraries. This is the complete list of libraries used. You'll have to import them in PlatformIO as global libraries

- Adafruit GFX Library by Adafruit, Ver. 1.2.9
- Adafruit PN532 by Adafruit, Ver. 1.0.2
- Adafruit ST7735 and ST7789 Library by Adafruit, Ver. 1.2.2
- ArduinoJson-esphomelib by Benoit Blanchon, Ver. 5.13.3
- ESP32httpUpdate by Matej Sychra, Ver. 2.1.145
- IFTTTWebhook by John Romkey, Ver. 1.1.2
- MFRC522 by Miguel Balboa, Ver. 1.3.6
- Paho by Eclipse, Ver. 1.0.0
- Time by Michael Margolis, Ver. 1.5
- U8g2 by oliver, Ver. 2.23.18
- ESP8266 and ESP32 Oled Driver for SSD1306 display by Daniel Eichhorn, Ver. 4.0.0

There are some more libraries used, but these are part of the project as they are not installable from the PlatformIO library management.You'll find them in the lib directory.
- AWS_IOT
- PubSubClient
- Syslog
- aws-mqtt-websockets
- aws-sdk-arduino-esp8266

## Initialize EEPROM
Before saving NFC unique IDs or a pricelist into the EEPROM, please make sure you initialized the EEPROM. 

You could either use the EEPROM-Tool from the c't ([link](https://github.com/psct/sharespresso/blob/master/EEPROM_tool/EEPROM_tool.ino)) 
or the original version from Oliver Krohn ([link](https://github.com/oliverk71/Coffeemaker-Payment-System/blob/master/EEPROM_tool.ino)). 
Simply adjust the memory settings to fit the size of the EEPROM of your controller and flash the sketch to the board. A textual menu 
will guide you.  

## Initialize BLE-Module (optional)
If you'd like to use a BLE-module and the native Android App, please follow the description of the c't magazin. We prefer to use our 
Ionic3-App :)

## Understand the modules
If you'd like to make changes to the code, please take a look at the [documentation of the modules](src/Modules.md).
