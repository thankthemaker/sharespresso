#ifndef ICOFFEEMAKER_H_
#define ICOFFEEMAKER_H_

#include "Arduino.h"
#include <map>
#include "settings.h"
#include "IDisplay.h"
#include "buzzer.h"

class ICoffeeMaker {
    public:
        IDisplay *oled;
        Buzzer *buzzer;
        // product codes send by coffeemakers "?PA<x>\r\n", just <x>    
        std::map <char, String> products;

        ICoffeeMaker(IDisplay *oled, Buzzer *buzzer);

        void initCoffeemaker();
        String fromCoffeemaker();
        void toCoffeemaker(String outputString);
        void servicetoggle(void);
        void inkasso_off(void);
        void inkasso_on(void);

        std::map <char, String>  getProducts();
        int getIndexForProduct(char productCode);
};

class CoffeeMakerFactory {
    public:
        static CoffeeMakerFactory* getInstance();
        ICoffeeMaker* createCoffeeMaker(IDisplay *oled, Buzzer *buzzer);

    private:
        CoffeeMakerFactory();    
        static CoffeeMakerFactory *instance;    
};
#endif
