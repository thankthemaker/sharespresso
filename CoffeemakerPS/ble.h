#ifndef BLE_H
#define BLE_H

#include "Arduino.h";
#ifndef ESP32
 #include <SoftwareSerial.h>;
#else
 #include <HardwareSerial.h>;
#endif

#include "settings.h";

#ifndef BLE_RX_PIN
 #define BLE_RX_PIN 7
#endif

#ifndef BLE_TX_PIN
 #define BLE_TX_PIN 8
#endif

class BleConnection {
    private:
#ifndef ESP32
 SoftwareSerial bleSerial;
#else
 HardwareSerial bleSerial;
#endif        
    public:
        BleConnection();

        void initBle();
        String readCommand();
#ifndef ESP32
 SoftwareSerial getSerial();
#else
 HardwareSerial getSerial();
#endif        
};
#endif

