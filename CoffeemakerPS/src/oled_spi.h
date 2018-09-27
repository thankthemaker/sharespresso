#ifndef OLED_H_
#define OLED_H_

#include "Arduino.h"
#include "IDisplay.h"
#include <U8g2lib.h>
#include <SPI.h>

class OledSpiDisplay : public IDisplay {
    public:
        OledSpiDisplay();

        void initDisplay();
        void print_logo();
        void message_print(String msg1, String msg2, int wait);
        void message_print(String msg1, String msg2, String msg3, int wait);
        void message_print(String msg1, String msg2, String msg3, String msg4, int wait);
        void message_print_scroll(String msg);
        void message_print_scroll_array(String msg[], int msgSize);
        void message_clear();
};
#endif