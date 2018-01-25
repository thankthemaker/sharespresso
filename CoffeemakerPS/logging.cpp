#include "logging.h"

CoffeeLogger::CoffeeLogger() : syslog(udpClient, SYSLOG_SERVER, SYSLOG_PORT, DEVICE_HOSTNAME, APP_NAME, LOG_KERN){
  Serial.println("staring syslog");
 }

String CoffeeLogger::print10digits(unsigned long number) {
  String(tempString) = String(number);
  String(newString) = "";
  int i = 10-tempString.length();
  for (int a = 0; a < (10-tempString.length()); a++){
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

String CoffeeLogger::printCredit(int credit){
  int euro = ((credit)/100);  //  int euro = ((credit*10)/100);
  int cent = ((credit)%100);  //  int cent = ((credit*10)%100); 
  String(output);
  output = String(euro);
  output += ',';
  output += String(cent);
  if (cent < 10){
    output += '0';
  }
  output += F(" EUR");  
  return output;
}

void CoffeeLogger::log(String msg) {
  log(LOG_INFO, msg);
}

void CoffeeLogger::log(uint16_t pri, String msg) {
#if defined(SERLOG)
  Serial.println(msg);
#endif
#if defined(SYSLOG)
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("send to syslog: " + msg);
    syslog.log(pri, msg); 
  }
#endif
}
