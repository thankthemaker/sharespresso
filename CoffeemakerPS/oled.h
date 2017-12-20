#include "Arduino.h"
#include "SSD1306Brzo.h" //OLED I2C

#ifndef SETTINGS_H_
 #include "settings.h"
#endif

#define OLED_H_

#ifndef OLED_SDA_PIN
 OLED_RX_PIN 4
#endif
#ifndef OLED_SDC_PIN
 OLED_TX_PIN 5
#endif

class OledDisplay {
    public:
        OledDisplay();

        void initOled();
        void message_print(String msg1, String msg2, int wait);
        void message_clear();
};
