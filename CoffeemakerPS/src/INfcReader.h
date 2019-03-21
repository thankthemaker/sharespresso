#ifndef INFCREADER_H
#define INFCREADER_H

#include "logging.h";
#include "settings.h";
#include "eepromconfig.h";
#include "IDisplay.h"
#include "buzzer.h";
#include "IMessageBroker.h"

#define MASTERCARD 3496110302 // card uid to enter/exit service mode

class INfcReader {
    private:
        IDisplay* oled;
        Buzzer* buzzer;
        IMessageBroker* messageBroker;
        CoffeeLogger logger;

    public:    
        // pure virtual (abstract) method definitions
        virtual void initNfcReader() = 0;
        virtual void registernewcards() = 0;
        virtual unsigned long nfcidread(void) = 0;
};

class NfcReaderFactory {
    public:
        static NfcReaderFactory* getInstance();
        INfcReader* createNfcReader(IDisplay *oled, Buzzer *buzzer);

    private:
        NfcReaderFactory();    
        static NfcReaderFactory *instance;    
};
#endif

