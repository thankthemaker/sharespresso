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

/** 
 * scroll a text of arraylines from bottom of display
 * to the top of the display and then out of display  
 */
void OledSpiDisplay::message_print_scroll_array(String msg[], int msgSize)
{
  u8g2.setFont(u8g2_font_ncenR12_tr);

  for (int ypos = u8g2.getDisplayHeight(); ypos > -(msgSize * (u8g2.getMaxCharHeight() + 1)) ; ypos--)
  {
    u8g2.clearBuffer();

    for (int i = 0; i < msgSize && msg[i] != NULL; i++) {
      //Serial.println(msg[i]);
      u8g2.setCursor(0, ypos + ((u8g2.getMaxCharHeight() + 1) * i));
      u8g2.print(msg[i]);
    }

    u8g2.sendBuffer();
    // scrollspeed
    delay(50);
  }
  delay(1);
}

/**
 * Splits the text in an array of lines
 * and invokes the message_print_scroll_array function
 * to display the text vertically scrolling
 */
void OledSpiDisplay::message_print_scroll(String msg)
{
  u8g2.setFont(u8g2_font_ncenR12_tr);
  // TODO use vector or list instead of static array. At the end of the method
  // this static array is copied into a fitting array
  String lines[30];
  int currentline = 0;

  const char *msgchars = msg.c_str();

  String textline;
  String newWord = "";

  textline = "";

  // iterate through text, extract the words and put them into lines
  // not bigger than the displaywidth
  while (*msgchars) {
    while (*msgchars) {
      newWord = newWord + *msgchars;
      if (*msgchars == ' ') {
        *msgchars++;
        break;
      }
      *msgchars++;
    }
    if (u8g2.getStrWidth((textline + newWord).c_str()) < u8g2.getDisplayWidth()) {
      textline = textline + newWord;
      newWord = "";
    } else {
      lines[currentline++] = textline;
      textline = newWord;
      newWord = "";
    }
  }

  lines[currentline] = textline;

  // delete whitespaces at the end of textlines and copy lines to new array of correct size
  int linesArraySize = currentline + 1;
  String linesWithFittingArray[linesArraySize];

  currentline = 0;
  while (currentline < linesArraySize && lines[currentline] != NULL) {
    long pos = lines[currentline].length();
    if (lines[currentline].substring(pos - 1) == " ") {
      lines[currentline] = lines[currentline].substring(0, pos - 1);
    }
    linesWithFittingArray[currentline] = lines[currentline];
    currentline++;
  }

  int linesWithFittingArraySize = (sizeof(linesWithFittingArray) / sizeof(linesWithFittingArray[0]));

  // invoke method to draw the lines to the display
  this->message_print_scroll_array(linesWithFittingArray, linesWithFittingArraySize);
}

void OledSpiDisplay::message_clear() {
  u8g2.clearDisplay();
}
