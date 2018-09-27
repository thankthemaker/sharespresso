#ifndef OLED_H_
#define OLED_H_

#include "Arduino.h"
#include "IDisplay.h"
#ifdef ESP8266
  // for ESP8266 use special optimized library 
  #include "SSD1306Brzo.h" //OLED I2C
#else
  #include "SSD1306.h"
#endif

class OledDisplay : public IDisplay {
    public:
        OledDisplay();

        void initDisplay();
        void print_logo();
        void message_print(String msg1, String msg2, int wait);
        void message_print(String msg1, String msg2, String msg3, int wait);
        void message_print(String msg1, String msg2, String msg3, String msg4, int wait);
        void message_print_scroll(String msg);
        void message_clear();
};
#endif

