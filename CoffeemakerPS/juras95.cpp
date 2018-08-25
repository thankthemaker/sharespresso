#include "juras95.h";

JuraS95::JuraS95(IDisplay *oled, Buzzer *buzzer) : ICoffeeMaker(oled, buzzer) {
  products['E'] = F("Small cup");
  products['F'] = F("2 small cups");
  products['A'] = F("Large cup");
  products['B'] = F("2 large cups");
  products['J'] = F("Steam 2");
  products['I'] = F("Steam 1");
  products['G'] = F("Extra large cup");
};

