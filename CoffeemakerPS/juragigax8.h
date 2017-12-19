#include "Arduino.h";
#include <SoftwareSerial.h>;
#ifndef OLED_H_
  #include "oled.h";
#endif
#ifndef BUZZER_H_
  #include "buzzer.h";
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

