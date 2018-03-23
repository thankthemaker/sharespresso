#include "juragigax8.h";

JuraGigaX8::JuraGigaX8(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['A'] = "Espresso";
  products['B'] = "Hot Water";
  products['C'] = "Hot Water";
  products['D'] = "Hot Water";
  products['E'] = "Hot Water";
  products['F'] = "Hot Water";
  products['G'] = "Latte Machiatto";
  products['H'] = "Hot Water";
  
  products['J'] = "Sonstiges";
};
