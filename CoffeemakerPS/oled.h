#include "Arduino.h"
#include "IDisplay.h"
#include "SSD1306Brzo.h" //OLED I2C

#define OLED_H_

#ifndef OLED_SDA_PIN
 OLED_RX_PIN 4
#endif
#ifndef OLED_SDC_PIN
 OLED_TX_PIN 5
#endif

class OledDisplay : virtual public IDisplay {
    public:
        OledDisplay();

        void init();
        void message_print(String msg1, String msg2, int wait);
        void message_clear();
};
