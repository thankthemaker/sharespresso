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

class INfcReader {
    private:
        OledDisplay* oled;
        Buzzer* buzzer;
        CoffeeLogger logger;

    public:    
        // pure virtual (abstract) method definitions
        virtual void registernewcards() = 0;
        virtual unsigned long nfcidread(void) = 0;
};
