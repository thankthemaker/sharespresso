#include "Arduino.h"

#define LOGGER_H_
#define SERLOG 1 // logging to serial port

class CoffeeLogger {
  public:
    CoffeeLogger();
  
    void serlog(String msg);
    String print2digits(int number);
    String print10digits(unsigned long number);
    String printCredit(int credit); 
};

