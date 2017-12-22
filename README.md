Sharespresso
============

is an IoT-Arduino-based NFC payment system for coffeemakers with
toptronic logic unit, as Jura Impressa S95 and others without
modifying the coffeemaker itself. 

Based on Oliver Krohns famous Coffeemaker-Payment-System at
https://github.com/oliverk71/Coffeemaker-Payment-System

and

the sharespresso project from the german c't at
https://github.com/psct/sharespresso
and
http://heise.de/-3058350

The coffeemaker payment system is connected to the internet via ESP68266 WiFi chipset. 

Hardware used: Sparkfun ESP8266 Thin Dev, AZDelivery 128x64 OLED, pn532 nfc card reader
reader (13.56MHz), HC-05 Bluetooth, buzzer

Features:
NFC-enabled payment system, useable with different payment methods (prepaid, crypto-coin, ...)
administration via MQTT and BLE, Ionic2(MQTT) and Android-App (BLE) available
OLED Display with animations ans status information
...


The code is provided 'as is', without any guarantuee. Use at your own
risk!

A reference for several included tools can be found here:
https://github.com/oliverk71/Coffeemaker-Payment-System
