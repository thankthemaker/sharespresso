#ifndef ICOFFEEMAKER_H_
#define ICOFFEEMAKER_H_

#include "Arduino.h"
#include "settings.h"
#include "IDisplay.h"
#include "buzzer.h"

class ICoffeeMaker {
    public:
        String productnames[20]; 
        IDisplay *oled;
        Buzzer *buzzer;

        ICoffeeMaker(IDisplay *oled, Buzzer *buzzer);

        void initCoffeemaker();
        String fromCoffeemaker();
        void toCoffeemaker(String outputString);
        void servicetoggle(void);
        void inkasso_off(void);
        void inkasso_on(void);

        // pure virtual (abstract) method definitions
        virtual char*  getProducts() = 0;
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
