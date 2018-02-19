#ifndef JURAGIGAX8_H
#define JURAGIGAX8_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "ICoffeeMaker.h"


#ifndef JURA_RX_PIN
  #define JURA_RX_PIN 15
#endif
#ifndef JURA_TX_PIN
  #define JURA_TX_PIN 16
#endif

class JuraGigaX8 : public ICoffeeMaker {
    public:
        // https://stackoverflow.com/questions/35413821/how-to-fix-this-array-used-as-initializer-error
        // product codes send by coffeemakers "?PA<x>\r\n", just <x>
        char products[11] = {'A', 'B', 'C', 'H', 'D', 'E', 'K', 'J', 'F', 'G', '\n'};
        JuraGigaX8(IDisplay *oled, Buzzer *buzzer);
        char* getProducts();
};
#endif