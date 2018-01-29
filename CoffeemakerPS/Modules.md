Modules
=======

Our version of the coffeemaker payment system is divided into several modules to make it easier to work in 
a collaborative way and to change some hardware parts.

## Core Module
The core module is located in the sketch CoffeemakerPS.ino itself. The main purpose of this module is to operate the 
mandatory Arduino setup() and loop() methods and to include the othe submodules.

## Submodules (alphabetically order)

### BLE
The BLE module is responsible for providing a bluetooth low energy connection for the native Android App. 

### Buzzer
The buzzer creates some typical tone sequences to indicate the current status of the system / payment process.

### EEPROM config
The EEPROM config module provides a highlevel interface for saving NFC unique IDs and the pricelist in the 
memory attached to the microcontroller. This is essential for the payment system to work autonomous in case 
the connection to the internet gets disturbed.

### Jura GIGA X8
This submodule handles the serial communication to the coffeemaker. At the moment it only provides an 
implementation for the Jura GIGA X8, but implementations for other coffeemakers may follow. 

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

### OLED
The OLED module makes use of the SSD1306 library from Adafruit and is able to display some information on a compatible OLED.

### PN532
This library is responsible for the communication with the NFC card reader. Every PN532-compatible reader should work.

### RC522 (not yet implemented)
This is an alternative library for the communication with the NFC card reader. 
Instead of the PN532 it uses a RC522 card reader, which is much cheaper 

### TFT (not yet implemented)
This module is an alternative for the OLED module. If you prefer to use a TFT instead a OLED, this module should work.
It's based on the Ardafruit GFX and ST7735 libraries.
