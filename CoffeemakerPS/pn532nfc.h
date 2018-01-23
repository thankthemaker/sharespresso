#include "INfcReader.h"
#include <Adafruit_PN532.h>; // NFC Card Reader

class Pn532NfcReader : public INfcReader{
    private:
        Adafruit_PN532* nfc;
        OledDisplay* oled;
        Buzzer* buzzer;
        CoffeeLogger logger;

    public:    
        Pn532NfcReader(Adafruit_PN532& nfc, OledDisplay& oled, Buzzer& buzzer);

        void registernewcards();
        unsigned long nfcidread(void);
};
