#include "juragigax8.h";

JuraGigaX8::JuraGigaX8(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['A'] = "Americano";
  products['B'] = "Kaffee groß";
  products['C'] = "Espresso";
  products['D'] = "Heißwasser";
  products['E'] = "Cappuccino groß";
  products['F'] = "Kaffee";
  products['G'] = "Milchkaffee";
  products['H'] = "Latte Machiatto";
  
  products['J'] = "Sonstiges";
};
