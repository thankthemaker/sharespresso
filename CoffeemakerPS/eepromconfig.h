#include "Arduino.h";
#include <EEPROM.h>
#include <WString.h>

#define EEPROMCONFIG_H_

#ifndef SETTINGS_H_
 #include "settings.h"
#endif

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
        cardlist_t readCards();

        void updatePricelist(pricelist_t pricelist);
        void updateCards(cardlist_t);

        int readCredit(int address);
        void updateCredit(int address, int credit);
        void deleteCard(int address, long card);
        void deleteCredit(int address, int credit);
};