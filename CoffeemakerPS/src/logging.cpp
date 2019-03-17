#include "logging.h"


CoffeeLogger::CoffeeLogger() {};


String CoffeeLogger::print12digits(unsigned long number) {
  String(tempString) = String(number);
  String(newString) = "";
  int i = 12-tempString.length();
  for (int a = 0; a < (12-tempString.length()); a++){
    newString += "0";
  }
  newString += number;
  return newString;
}

String CoffeeLogger::print2digits(int number) {
  String partString;
  if (number >= 0 && number < 10) {
    partString = "0";
    partString += number;
  } 
  else partString = String(number);
  return partString;
}

void CoffeeLogger::log(String msg) {
  log(LOG_INFO, msg);
}

void CoffeeLogger::log(uint16_t pri, String msg) {
#ifndef DEBUG 
 if(pri == LOG_DEBUG) {
   return;
 }
#endif

#if defined(SERLOG)
  Serial.println(msg);
#endif
}

