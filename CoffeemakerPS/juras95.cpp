#include "juras95.h";

JuraS95::JuraS95(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  /*
   productnames[0] = F("Cappuccino");
   productnames[1] = F("Espresso");
   productnames[2] = F("Espresso dopio");
   productnames[3] = F("Milchkaffee"); 
   productnames[4] = F("Kaffee");
   productnames[5] = F("Kaffee gross");
   productnames[6] = F("Dampf links");
   productnames[7] = F("Dampf rechts"); 
   productnames[8] = F("Portion Milch"); 
   productnames[9] = F("Caffee Latte"); 
   */
};

char* JuraS95::getProducts() {
  return products;
};
