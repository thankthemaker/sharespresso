#include "rc522nfc.h";

Rc522NfcReader::Rc522NfcReader(IDisplay *oled, Buzzer *buzzer) : nfc(RC522_SS, RC522_RST){
  this->oled = oled;
  this->buzzer = buzzer;
};

void Rc522NfcReader::initNfcReader() {
  this->nfc.PCD_Init();		// Init MFRC522
  this->nfc.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
}

void Rc522NfcReader::registernewcards() {
  unsigned long RFIDcard = 0;
  unsigned long actTime = millis();
  EEPROMConfig eepromConfig;
  cardlist_t cardlist =  eepromConfig.readCards();

  Serial.println(F("registernewcards entered"));
  do {
    RFIDcard = 0;
    delay(100); // Make our ESP8266 Watchdog happy
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
    Serial.println(F("registernewcards exited"));
}

unsigned long Rc522NfcReader::nfcidread(void) {
  unsigned long id=0;

  if ( ! this->nfc.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! this->nfc.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // ugly hack: fine for mifare classic (4 byte)
  // also fine for our ultras (last 4 bytes ever the same)
  // nfc.PrintHex(uid, uidLength);
    id = (unsigned long)this->nfc.uid.uidByte[0]<<24;
    id += (unsigned long)this->nfc.uid.uidByte[1]<<16;
    id += (unsigned long)this->nfc.uid.uidByte[2]<<8;
    id += (unsigned long)this->nfc.uid.uidByte[3];
  this->nfc.PICC_HaltA(); // Stop reading
  return id;
}

