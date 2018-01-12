#include "nfcreader.h";

NfcReader::NfcReader(Adafruit_PN532& nfc, OledDisplay& oled, Buzzer& buzzer) {
  this->nfc = &nfc;
  this->oled = &oled;
  this->buzzer = &buzzer;
};

void NfcReader::registernewcards() {
  unsigned long RFIDcard = 0;
  unsigned long actTime = millis();
  EEPROMConfig eepromConfig;
  cardlist_t cardlist =  eepromConfig.readCards();

  do {
    RFIDcard = 0;
    do {
      RFIDcard = this->nfcidread();
      if (RFIDcard != 0) {
        this->oled->message_clear();
        break;
      }
    } while ( (millis()-actTime) < 60 );  
    int k = 255;
    if (RFIDcard != 0) {
      if ( RFIDcard == MASTERCARD) {
        break;
      }
      for(int i=0;i<MAX_CARDS;i++){
        if (RFIDcard == cardlist.cards[i].card) {
          this->oled->message_print(logger.print10digits(RFIDcard), F("already exists"), 0);
          this->buzzer->beep(2);
          k=254;         
          break;
        }
        if ((cardlist.cards[i].card == 0) && (k == 255)) { // find first empty slot
          k=i;
        }
      }
      if ( k == 255) {
        this->oled->message_print(F("no slot left"),F(""),0);         
        break;
      }
      if ( k != 254) {
        this->oled->message_print( logger.print10digits(RFIDcard), F("registered"),0);
        int credit=1000;
//        int credit= EEPROM.readInt(1000+2*10);
        cardlist.cards[k].card = RFIDcard;
        eepromConfig.updateCards(cardlist);
//        EEPROM.updateInt(k*6+4, credit);
        this->buzzer->beep(1);
      }
      actTime = millis();
    }
  } while ( (millis()-actTime) < 10000 );
  this->oled->message_print(F("Registering"),F("ended"),2000);
  this->buzzer->beep(3);  
}

unsigned long NfcReader::nfcidread(void) {
  unsigned long id=0;
  uint8_t success;
  uint8_t uid[] = { 0,0,0,0,0,0,0,0 };
  uint8_t uidLength;
  success = this->nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);  
  if (success) {
    // ugly hack: fine for mifare classic (4 byte)
    // also fine for our ultras (last 4 bytes ever the same)
    // nfc.PrintHex(uid, uidLength);
    id = (unsigned long)uid[0]<<24;
    id += (unsigned long)uid[1]<<16;
    id += (unsigned long)uid[2]<<8;
    id += (unsigned long)uid[3];
  }
  return id;
}
