#include "Arduino.h"
#include "IDisplay.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#define TFT_H_

#ifndef TFT_CS
  #define TFT_CS 10
#endif
#ifndef TFT_RST
  #define TFT_RST 9
#endif
#ifndef TFT_DC
  #define TFT_DC 8
#endif

class TftDisplay : virtual public Display {
    public:
        TftDisplay();

        void init();
        void message_print(String msg1, String msg2, int wait);
        void message_clear();
};