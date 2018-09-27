#ifndef TFT_H_
#define TFT_H_

#include "Arduino.h"
#include "IDisplay.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SD.h>

class TftDisplay : public IDisplay {
    public:
        TftDisplay();

        void initDisplay();
        void print_logo();
        void message_print(String msg1, String msg2, int wait);
        void message_print(String msg1, String msg2, String msg3, int wait);
        void message_print(String msg1, String msg2, String msg3, String msg4, int wait);
        void message_print_scroll(String msg);
        void message_clear();

    private:
        void bmpDraw(char *filename, uint8_t x, uint8_t y);
        uint16_t read16(File f);
        uint32_t read32(File f);
};
#endif

