#ifndef JURAX7_H
#define JURAX7_H

#include "ICoffeeMaker.h"

class JuraX7 : public ICoffeeMaker {
  public:
    // product codes send by coffeemakers "?PA<x>\r\n", just <x>    
    //std::map <char, String> products;
    JuraX7(IDisplay *oled, Buzzer *buzzer);
    //std::map <char, String> getProducts();
    //int getIndexForProduct(char productCode);
};
#endif