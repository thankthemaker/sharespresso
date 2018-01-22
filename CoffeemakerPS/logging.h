#include "Arduino.h"
#ifdef SYSLOG
  #include <Syslog.h> // https://github.com/tomoconnor/ardusyslog/
#endif


#define LOGGER_H_

class CoffeeLogger {
  public:
    CoffeeLogger();
  
    void serlog(String msg);
    String print2digits(int number);
    String print10digits(unsigned long number);
    String printCredit(int credit); 
};

