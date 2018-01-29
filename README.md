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

Hardware used: 

* Sparkfun ESP8266 Thing Dev https://www.sparkfun.com/products/13711, 
* AZDelivery 128x64 OLED https://www.amazon.de/AZDelivery-Display-Arduino-Raspberry-gratis/dp/B01L9GC470, 
* pn532 nfc card reader (13.56MHz) http://www.elecfreaks.com/estore/nfc-rfid-breakout-module.html, 
* DSD Tech HC-05 Bluetooth https://www.amazon.de/dp/B01G9KSAF6/ref=pe_3044161_185740101_TE_item, 
* Piezo Summer Micro Buzzer 3-24V 

Features:

* NFC-enabled payment system, useable with different payment methods (prepaid, crypto-coin, ...)
* administration via MQTT and BLE, Ionic3(MQTT) and Android-App (BLE) available
* OLED Display with animations and status information
* ...


The code is provided 'as is', without any guarantuee. Use at your own
risk!

A reference for several included tools can be found here:
https://github.com/oliverk71/Coffeemaker-Payment-System
