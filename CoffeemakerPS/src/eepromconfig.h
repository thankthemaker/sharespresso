#ifndef EEPROMCONFIG_H_
#define EEPROMCONFIG_H_

#include "Arduino.h";
#include <EEPROM.h>
#include <WString.h>
#include "settings.h"

typedef struct {
    uint32_t card;
    uint16_t credit;
} card_t;

typedef struct {
    card_t cards[MAX_CARDS];
} cardlist_t;

typedef struct {
    uint16_t prices[10];
    uint16_t defaultCredit;
} pricelist_t;

class EEPROMConfig {
    public:
        EEPROMConfig();

        pricelist_t readPricelist();
        void updatePricelist(pricelist_t pricelist);
};
#endif

