#include "eepromconfig.h";

    EEPROMConfig::EEPROMConfig() {}

    int EEPROMConfig::readPrice(int address) {
        return 0;
    }
    
    long EEPROMConfig::readCard(int address){
        return 12345678;
    }

    int EEPROMConfig::readCredit(int address){
        return 1000;
    }

    void EEPROMConfig::writeCredit(int address, int credit){

    }

    void EEPROMConfig::deleteCard(int address, long card){

    }

    void EEPROMConfig::deleteCredit(int address, int credit){

    }