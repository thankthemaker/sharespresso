#ifndef OLED_H_
#define OLED_H_

#include "Arduino.h"
#include "IDisplay.h"
#include "SSD1306Brzo.h" //OLED I2C

class OledDisplay : public IDisplay {
    public:
        OledDisplay();

        void initDisplay();
        void print_logo();
        void message_print(String msg1, String msg2, int wait);
        void message_print_scroll(String msg);
        void message_clear();
};
#endif
