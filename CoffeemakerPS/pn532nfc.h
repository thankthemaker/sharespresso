#include <Adafruit_PN532.h>; // NFC Card Reader
#ifndef LOGGER_H_
  #include "logging.h";
#endif
#ifndef SETTINGS_H_
 #include "settings.h";
#endif
#ifndef EEPROMCONFIG_H_
 #include "eepromconfig.h";
#endif
#ifndef OLED_H_
  #include "oled.h";
#endif
#ifndef BUZZER_H_
  #include "buzzer.h";
#endif

#define MASTERCARD 3496110302 // card uid to enter/exit service mode

class NfcReader {
    private:
        Adafruit_PN532* nfc;
        OledDisplay* oled;
        Buzzer* buzzer;
        CoffeeLogger logger;

    public:    
        NfcReader(Adafruit_PN532& nfc, OledDisplay& oled, Buzzer& buzzer);

        void registernewcards();
        unsigned long nfcidread(void);
};
