# First steps

## Edit settings.h
Please take a look at the settings.h file in the project. Here you have all parameters in a single place and you have to a adjust 
some parameters, e.g. the SSID and credential for your WiFi and the settings for the MQTT connection to make the sketch work as 
expected. 

## Initialize EEPROM
Before saving NFC unique IDs or a pricelist into the EEPROM, please make sure you initialized the EEPROM. 

You could either use the EEPROM-Tool from the c't ([link](https://github.com/psct/sharespresso/blob/master/EEPROM_tool/EEPROM_tool.ino)) 
or the original version from Oliver Krohn ([link](https://github.com/oliverk71/Coffeemaker-Payment-System/blob/master/EEPROM_tool.ino)). 
Simply adjust the memory settings to fit the size of the EEPROM of your controller and flash the sketch to the board. A textual menu 
will guide you.  

## Initialize BLE-Module (optional)
If you'd like to use a BLE-module and the native Android App, please follow the description of the c't magazin. We prefer to use our 
Ionic3-App :)
