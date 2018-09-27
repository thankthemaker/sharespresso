#ifndef JURAGIGAX8_H
#define JURAGIGAX8_H

#include "Arduino.h"
#include <map>
#include "ICoffeeMaker.h"
#ifndef ESP32
 #include <SoftwareSerial.h>;
#else
 #include <HardwareSerial.h>;
#endif

#ifndef JURA_RX_PIN
  #define JURA_RX_PIN 15
#endif
#ifndef JURA_TX_PIN
  #define JURA_TX_PIN 16
#endif

class JuraGigaX8 : public ICoffeeMaker {
    public:
        // product codes send by coffeemakers "?PA<x>\r\n", just <x>    
        //std::map <char, String> products;
        JuraGigaX8(IDisplay *oled, Buzzer *buzzer);
        //std::map <char, String>  getProducts();
        //int getIndexForProduct(char productCode);
};
#endif

