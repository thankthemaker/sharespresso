#ifndef JOURNAL_H_
#define JOURNAL_H_

#include <SPI.h>
#include <SD.h>
#include "settings.h"

class Journal {
  public:
    Journal();

    void initJournal();
    void writeJournal(String timestamp, String cardId, String product, String price);
    String exportJournal();
};
#endif