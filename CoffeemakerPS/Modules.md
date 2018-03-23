Modules
=======

Our version of the coffeemaker payment system is divided into several modules to make it easier to work in 
a collaborative way and to change some hardware parts.

## Core Module
The core module is located in the sketch CoffeemakerPS.ino itself. The main purpose of this module is to operate the 
mandatory Arduino setup() and loop() methods and to include the othe submodules.

## Submodules (alphabetically order)

### AWS IoT 
This module integrates Amazon Webservice IoT Core into the payment system, which makes it possible to to awesome thing in the cloud. It's possible to store events from the coffeemaker in a DynamoDB or trigger a Lambda function. 

### BLE
The BLE module is responsible for providing a bluetooth low energy connection for the native Android App. 

### Buzzer
The buzzer creates some typical tone sequences to indicate the current status of the system / payment process.

### Coffeemaker
This submodule handles the serial communication to the coffeemaker. It is implemented as an interface, which makes it possible to easiely support diffrent coffemakers. At the moment there are implementations for Jura Giga X8, Jura X7 and Jura S95. Feel free to add your own model. 

#### Jura GIGA X8
This is the implementation for the Jura GIGA X8. 

#### Jura X7
This is the implementation for the Jura GIGA X7. 

#### Jura S95
This is the implementation for the Jura GIGA S95. 

### Display (OLED or TFT)
The displa module is also an interface. It supports two different display types.

#### OLED
The OLED module makes use of the SSD1306 library from Adafruit and is able to display some information on a compatible OLED.

#### TFT
This module is an alternative for the OLED module. If you prefer to use a TFT instead a OLED, this module should work.
It's based on the Ardafruit GFX and ST7735 libraries. Many TFT-diplays are shipped with a SD-Cardreader which is also supported (see Journal-module).

### EEPROM config
The EEPROM config module provides a highlevel interface for saving NFC unique IDs and the pricelist in the 
memory attached to the microcontroller. This is essential for the payment system to work autonomous in case 
the connection to the internet gets disturbed.

### Journal (on SD-Card)
The journal module is responsible for storing coffeemaker events to a locally mounted SD-card.

### Logging
The logging submodule provides a simple API for logging purpose. There are two channel, which can be activated separately.

#### Serial
Logging is done over the standard serial communication. This is useful in case the IoT-device is still connected to
a computer.

#### Syslog
The log statements are send to a normal syslog host. This is useful in "production mode" when the device is disconnected 
from the serial line.

### MQTT
The MQTT submodule is based on the Arduino PubSubClient library and handles the MQTT connection and message handling. 

### NFC Reader (& Writer)
The NFC module is also designed as a abstract interface to support different types of NFC/RFID reader.

#### PN532
This library is responsible for the communication with the NFC card reader. Every PN532-compatible reader should work.

#### RC522
This is an alternative library for the communication with the NFC card reader. 
Instead of the PN532 it uses a RC522 card reader, which is much cheaper 

### NTP
Most Arduino-compatible PCB are missing a RTC. The NTP module connects to a NTP server an updates the time.

### OTA Update
The OTA-update enables the payment system to receive firmware updates over-the-air.

