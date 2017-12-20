#include "Arduino.h";
#include <SoftwareSerial.h>;

#ifndef SETTINGS_H_
 #include "settings.h";
#endif

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