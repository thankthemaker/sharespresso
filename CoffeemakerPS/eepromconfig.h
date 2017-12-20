#include "Arduino.h";
#include <EEPROM.h>

class Config {

};

class EEPROMConfig {
    public:
        EEPROMConfig();

        int readPrice(int address);
        long readCard(int address);
        int readCredit(int address);

        void writeCredit(int address, int credit);

        void deleteCard(int address, long card);
        void deleteCredit(int address, int credit);
};