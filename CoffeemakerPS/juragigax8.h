#include "Arduino.h";
#include <SoftwareSerial.h>;

#ifndef SETTINGS_H_
 #include "settings.h"
#endif
#ifndef OLED_H_
  #include "oled.h";
#endif
#ifndef BUZZER_H_
  #include "buzzer.h";
#endif

#ifndef JURA_RX_PIN
  #define JURA_RX_PIN 15
#endif
#ifndef JURA_TX_PIN
  #define JURA_TX_PIN 16
#endif

class JuraGigaX8 {
    private:
        OledDisplay* oled;
        Buzzer* buzzer;

    public:
        JuraGigaX8(OledDisplay& oled, Buzzer& buzzer);

        void initCoffeemaker();
        String fromCoffeemaker();
        void toCoffeemaker(String outputString);
        void servicetoggle(void);
        void inkasso_off(void);
        void inkasso_on(void);
};

