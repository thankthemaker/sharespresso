#ifndef PN532NFCREADER_H
#define PN532NFCREADER_H

#include "INfcReader.h"
#include <SPI.h>
#include <Adafruit_PN532.h>; // NFC Card Reader

class Pn532NfcReader : public INfcReader{
    private:
        Adafruit_PN532 nfc;
        IDisplay *oled;
        Buzzer *buzzer;
        CoffeeLogger logger;

    public:    
        Pn532NfcReader(IDisplay *oled, Buzzer *buzzer);

        void initNfcReader();
        void registernewcards();
        unsigned long nfcidread(void);
};
#endif

