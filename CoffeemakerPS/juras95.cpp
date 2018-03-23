#include "juras95.h";

JuraS95::JuraS95(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['E'] = "Small cup";
  products['F'] = "2 small cups";
  products['A'] = "Large cup";
  products['B'] = "2 large cups";
  products['J'] = "Steam 2";
  products['I'] = "Steam 1";
  products['G'] = "Extra large cup";
};
