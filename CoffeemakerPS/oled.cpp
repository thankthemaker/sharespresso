#include "oled.h";

SSD1306Brzo display(0x3c, OLED_SDA_PIN, OLED_SDC_PIN);

OledDisplay::OledDisplay() {}

void OledDisplay::initDisplay() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  display.drawString(0, 26, "Welcome to Coffeemaker");
  display.display(); 
}

void OledDisplay::message_print(String msg1, String msg2, int wait) {
#if defined(SERLOG)
  if (msg1 != "") { Serial.print(msg1 + " "); }
  if (msg2 != "") { Serial.print(msg2); }
  if ((msg1 != "") || (msg2 != "")) { Serial.println(""); }
#endif
  display.clear();
  if (msg1 != "") {
    display.drawString(0, 10, msg1);
  }
  if (msg2 != "") {
    display.drawString(0, 30, msg2);
  }
  display.display(); 
  if (wait > 0) { 
    delay(wait);
      display.clear();
  }
}

void OledDisplay::message_clear() {
  display.clear();
}
