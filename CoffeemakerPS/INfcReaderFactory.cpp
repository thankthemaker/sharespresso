#include "INfcReader.h"

#if defined(PN532)
 #include "pn532nfc.h"
#elif defined(RC522)
 #include "rc522nfc.h"
#endif

NfcReaderFactory* NfcReaderFactory::instance = 0;

NfcReaderFactory::NfcReaderFactory() {}

NfcReaderFactory* NfcReaderFactory::getInstance() {
    if (instance == 0)
    {
        instance = new NfcReaderFactory();
    }

    return instance;
}

INfcReader* NfcReaderFactory::createNfcReader(IDisplay *oled, Buzzer *buzzer) {
#if defined(PN532)
 return new Pn532NfcReader(oled, buzzer);
#elif defined(RC522)
 return new Rc522NfcReader(oled, buzzer);
#endif
}

