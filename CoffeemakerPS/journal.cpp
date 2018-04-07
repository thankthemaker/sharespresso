#include "journal.h"

Journal::Journal() {}

void Journal::initJournal() {
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CARD_CS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void Journal::writeJournal(String timestamp, String cardId, String product, String price) {

  String data = timestamp + ";" + cardId + ";" + product + ";" + price;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("journal.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
//    Serial.println(data);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening journal.csv");
  }
}

String Journal::exportJournal() {
  return "";
}






