#include "Arduino.h"
#include "SSD1306Brzo.h" //OLED I2C

#define OLED_H_

class OledDisplay {
    public:
        OledDisplay();

        void initOled();
        void message_print(String msg1, String msg2, int wait);
        void message_clear();
};
