#ifndef RC522NFCREADER_H
#define RC522NFCREADER_H

#include "INfcReader.h"
#include <MFRC522.h>
#include "IMessageBroker.h"

class Rc522NfcReader : public INfcReader{
    private:
        MFRC522 nfc;
        IDisplay *oled;
        Buzzer* buzzer;
        IMessageBroker* messageBroker;
        CoffeeLogger logger;

    public:    
        Rc522NfcReader(IMessageBroker *messageBroker, IDisplay *oled, Buzzer *buzzer);

        void initNfcReader();
        void registernewcards();
        unsigned long nfcidread(void);
};
#endif

