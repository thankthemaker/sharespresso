#ifndef TFT_H_
#define TFT_H_

#include "Arduino.h"
#include "IDisplay.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

class TftDisplay : public IDisplay {
    public:
        TftDisplay();

        void initDisplay();
        void message_print(String msg1, String msg2, int wait);
        void message_clear();
};
#endif