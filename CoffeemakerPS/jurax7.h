#ifndef JURAX7_H
#define JURAX7_H

#include "ICoffeeMaker.h"

class JuraX7 : public ICoffeeMaker {
  public:
    // https://stackoverflow.com/questions/35413821/how-to-fix-this-array-used-as-initializer-error
    // product codes send by coffeemakers "?PA<x>\r\n", just <x>
    char products[11] = {'A', 'B', 'C', 'H', 'D', 'E', 'K', 'J', 'F', 'G', '\n'};
    JuraX7(IDisplay *oled, Buzzer *buzzer);
    char* getProducts();
};
#endif