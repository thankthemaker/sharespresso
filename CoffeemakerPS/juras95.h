#ifndef JURAS95_H
#define JURAS95_H

#include "ICoffeeMaker.h"

class JuraS95 : public ICoffeeMaker {
  public:
    // https://stackoverflow.com/questions/35413821/how-to-fix-this-array-used-as-initializer-error
    // product codes send by coffeemakers "?PA<x>\r\n", just <x>
    char products[11] = {'E', 'F', 'A', 'B', 'J', 'I', 'G', '\n'};
    JuraS95(IDisplay *oled, Buzzer *buzzer);
    char* getProducts();
};
#endif