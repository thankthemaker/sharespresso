#ifndef BLE_H
#define BLE_H

#include "Arduino.h";
#include <SoftwareSerial.h>;

 #include "settings.h";

#ifndef BLE_RX_PIN
 #define BLE_RX_PIN 7
#endif

#ifndef BLE_TX_PIN
 #define BLE_TX_PIN 8
#endif

class BleConnection {
    private:
        SoftwareSerial myBT;
    public:
        BleConnection();

        void initBle();
        String readCommand();
        SoftwareSerial getSerial();
};
#endif