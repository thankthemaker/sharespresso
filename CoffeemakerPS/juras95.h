#ifndef JURAS95_H
#define JURAS95_H

#include "ICoffeeMaker.h"

class JuraS95 : public ICoffeeMaker {
  public:
    // product codes send by coffeemakers "?PA<x>\r\n", just <x>    
    //std::map <char, String> products;
    JuraS95(IDisplay *oled, Buzzer *buzzer);
    //std::map <char, String> getProducts();
    //int getIndexForProduct(char productCode);
};
#endif