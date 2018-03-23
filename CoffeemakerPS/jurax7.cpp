#include "jurax7.h";

JuraX7::JuraX7(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['A'] = "Cappuccino";
  products['B'] = "Espresso";
  products['C'] = "Espresso dopio";
  products['H'] = "Milchkaffee";
  products['D'] = "Kaffee";
  products['E'] = "Kaffee gross";
  products['K'] = "Dampf links";
  products['J'] = "Dampf rechts";
  products['F'] = "Portion Milch";
  products['G'] = "Caffee Latte";
};

