#include "eepromconfig.h";
#include "EEPROM.h";

    EEPROMConfig::EEPROMConfig() {}

    pricelist_t EEPROMConfig::readPricelist() {
        pricelist_t pricelist;
        int size = sizeof(pricelist);
        Serial.printf_P(PSTR("size of pricelist: %d  Byte"), size);
        EEPROM.begin(EEPROM_SIZE_BYTES);
        EEPROM.get(PRICELIST_ADDRESS_OFFSET, pricelist);
        EEPROM.end();
        return pricelist;
    }


    void EEPROMConfig::updatePricelist(pricelist_t pricelist) {
          // Save prices from RAM into EEPROM
        EEPROM.begin(EEPROM_SIZE_BYTES);
        EEPROM.put(PRICELIST_ADDRESS_OFFSET, pricelist);
        delay(200);
        EEPROM.commit(); // Only needed for ESP8266 to get data written
        EEPROM.end();   
    }