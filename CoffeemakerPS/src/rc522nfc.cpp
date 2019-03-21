#include "rc522nfc.h";

Rc522NfcReader::Rc522NfcReader(IMessageBroker *messageBroker, IDisplay *oled, Buzzer *buzzer) : nfc(RC522_SS, RC522_RST){
  this->oled = oled;
  this->buzzer = buzzer;
  this->messageBroker = messageBroker;
};

void Rc522NfcReader::initNfcReader() {
  this->nfc.PCD_Init();		// Init MFRC522
  this->nfc.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
}

void Rc522NfcReader::registernewcards() {
  unsigned long RFIDcard = 0;
  unsigned long actTime = millis();

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
    if (RFIDcard != 0) {
      this->messageBroker->sendmessage(logger.print12digits(RFIDcard), 3);
      this->oled->message_print( logger.print12digits(RFIDcard), F("registered"),0);
      this->buzzer->beep(1);
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

