#include "eepromconfig.h";
#include "EEPROM.h";

    EEPROMConfig::EEPROMConfig() {}

    pricelist_t EEPROMConfig::readPricelist() {
        pricelist_t pricelist;
        int size = sizeof(pricelist);
        Serial.printf_P(PSTR("size of pricelist: %d  Byte"), size);
        if(!EEPROM.begin(EEPROM_SIZE_BYTES)) {
          Serial.println(F("Failed to initialise EEPROM"));
          Serial.println(F("Restarting..."));
          delay(1000);
          ESP.restart();
        }
        EEPROM.get(PRICELIST_ADDRESS_OFFSET, pricelist);
        EEPROM.end();
        return pricelist;
    }

    cardlist_t EEPROMConfig::readCards() {
        cardlist_t cardlist;
        int size = sizeof(cardlist);
        Serial.printf_P(PSTR("size of cardlist: %d Byte"), size);
        if(!EEPROM.begin(EEPROM_SIZE_BYTES)) {
          Serial.println(F("Failed to initialise EEPROM"));
          Serial.println(F("Restarting..."));
          delay(1000);
          ESP.restart();
        }
        EEPROM.get(0, cardlist );
        EEPROM.end();
        return cardlist;
    }

    void EEPROMConfig::updatePricelist(pricelist_t pricelist) {
          // Save prices from RAM into EEPROM
        if(!EEPROM.begin(EEPROM_SIZE_BYTES)) {
          Serial.println(F("Failed to initialise EEPROM"));
          Serial.println(F("Restarting..."));
          delay(1000);
          ESP.restart();
        }
        EEPROM.put(PRICELIST_ADDRESS_OFFSET, pricelist);
        delay(200);
        EEPROM.commit(); // Only needed for ESP8266 to get data written
        EEPROM.end();   
    }

    void EEPROMConfig::updateCards(cardlist_t cardlist) {
          // Save cards from RAM into EEPROM
        if(!EEPROM.begin(EEPROM_SIZE_BYTES)) {
          Serial.println(F("Failed to initialise EEPROM"));
          Serial.println(F("Restarting..."));
          delay(1000);
          ESP.restart();
        }
        EEPROM.put(0, cardlist);
        delay(200);
        EEPROM.commit(); // Only needed for ESP8266 to get data written
        EEPROM.end();   
    }

    int EEPROMConfig::readCredit(int address) {
        return 1000;
    }
    void EEPROMConfig::updateCredit(int address, int credit) {}
    void EEPROMConfig::deleteCard(int address, long card) {}
    void EEPROMConfig::deleteCredit(int address, int credit) {}

