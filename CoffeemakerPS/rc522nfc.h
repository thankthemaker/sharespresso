#ifndef RC522NFCREADER_H
#define RC522NFCREADER_H

#include "INfcReader.h"
#include <MFRC522.h>

class Rc522NfcReader : public INfcReader{
    private:
        MFRC522 nfc;
        IDisplay *oled;
        Buzzer* buzzer;
        CoffeeLogger logger;

    public:    
        Rc522NfcReader(IDisplay *oled, Buzzer *buzzer);

        void initNfcReader();
        void registernewcards();
        unsigned long nfcidread(void);
};
#endif