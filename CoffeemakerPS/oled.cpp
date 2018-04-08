#include "oled.h";

SSD1306Brzo display(0x3c, OLED_SDA_PIN, OLED_SCL_PIN);

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

void print_logo() {}

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

void OledDisplay::message_print_scroll(String msg) {
  display.setFont(ArialMT_Plain_16);
  // ArialMT_Plain_16 = 19px
  int fontsize = 19;
  int displaywidth = 128;
  int displayheight = 64;

  int stringwidth = display.getStringWidth(msg);
  
  // cannot calculate exact textlines because of word-wraps 
  // -> add three lines for offset.
  // change this if you have an idea how to calculate exact textlines 
  // from a given msg. 
  int lines = (stringwidth / displaywidth) + 3;
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  for (int i=128; i>-(lines * fontsize); i--){
    display.clear();
    display.drawStringMaxWidth(0, i, 128, msg);  
    display.display();
    // scrollspeed
    delay(50);
  }
  delay(1);
}

void OledDisplay::message_clear() {
  display.clear();
}
