#include "jurax7.h";

JuraX7::JuraX7(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['A'] = F("Cappuccino");
  products['B'] = F("Espresso");
  products['C'] = F("Espresso dopio");
  products['H'] = F("Milchkaffee");
  products['D'] = F("Kaffee");
  products['E'] = F("Kaffee gross");
  products['K'] = F("Dampf links");
  products['J'] = F("Dampf rechts");
  products['F'] = F("Portion Milch");
  products['G'] = F("Caffee Latte");
};


