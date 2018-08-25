#include "juragigax8.h";

JuraGigaX8::JuraGigaX8(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['A'] = F("Americano");
  products['B'] = F("Kaffee groß");
  products['C'] = F("Espresso");
  products['D'] = F("Heißwasser");
  products['E'] = F("Cappuccino groß");
  products['F'] = F("Kaffee");
  products['G'] = F("Milchkaffee");
  products['H'] = F("Latte Machiatto");
  
  products['J'] = F("Sonstiges");
};

