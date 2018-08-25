#include "oled_spi.h";

//U8G2_SSD1327_MIDAS_128X128_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 15, /* reset=*/ 8); // PageBuffer
U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 15, /* reset=*/ 8); // FullBuffer

OledSpiDisplay::OledSpiDisplay() {}

void OledSpiDisplay::initDisplay() {
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB12_tr);
  u8g2.drawStr(20,24, "Welcome to");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(60,24, "Sharepresso");
  u8g2.sendBuffer();
}

void OledSpiDisplay::print_logo() {}

void OledSpiDisplay::message_print(String msg1, String msg2, int wait) {
  this->message_print(msg1, msg2, "", "", wait);
}

void OledSpiDisplay::message_print(String msg1, String msg2, String msg3, int wait) {
  this->message_print(msg1, msg2, "", "", wait);
}

void OledSpiDisplay::message_print(String msg1, String msg2, String msg3, String msg4, int wait) {
#if defined(SERLOG)
  if (msg1 != "") { Serial.print(msg1 + " "); }
  if (msg2 != "") { Serial.print(msg2); }
  if ((msg1 != "") || (msg2 != "")) { Serial.println(""); }
#endif
    u8g2.clearBuffer();
    if (msg1 != "") {
      u8g2.setFont(u8g2_font_ncenB12_tr);
      u8g2.drawStr(0, 20, msg1.c_str());
    }
    if (msg2 != "") {
      u8g2.setFont(u8g2_font_ncenB10_tr);
      u8g2.drawStr(0, 40, msg2.c_str());
    }
    if (msg3 != "") {
      u8g2.setFont(u8g2_font_ncenB10_tr);
      u8g2.drawStr(0, 60, msg3.c_str());
    }
    if (msg4 != "") {
      u8g2.setFont(u8g2_font_ncenB10_tr);
      u8g2.drawStr(0, 80, msg4.c_str());
    }
    u8g2.sendBuffer();
    if (wait > 0) { 
      delay(wait);
      u8g2.clearDisplay();
    }
}


void OledSpiDisplay::message_print_scroll(String msg) {
  u8g2.setFont(u8g2_font_ncenB12_tr);
  int fontsize = 12;
  int displaywidth = 128;
  int displayheight = 128;

  int stringwidth = u8g2.getStrWidth(msg.c_str());
  
  // cannot calculate exact textlines because of word-wraps 
  // -> add three lines for offset.
  // change this if you have an idea how to calculate exact textlines 
  // from a given msg. 
  int lines = (stringwidth / displaywidth) + 3;

  for (int i=128; i>-(lines * fontsize); i--){
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.drawStr(0, i, msg.c_str());
    u8g2.sendBuffer();          // transfer internal memory to the display
    // scrollspeed
    delay(50);
  }
  delay(1);
}

void OledSpiDisplay::message_clear() {
  u8g2.clearDisplay();
}

