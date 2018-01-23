#include "INfcReader.h"
#include <MFRC522.h>

class Rc522NfcReader : public INfcReader{
    private:
        MFRC522* nfc;
        OledDisplay* oled;
        Buzzer* buzzer;
        CoffeeLogger logger;

    public:    
        Rc522NfcReader(MFRC522& nfc, OledDisplay& oled, Buzzer& buzzer);

        void registernewcards();
        unsigned long nfcidread(void);
};
