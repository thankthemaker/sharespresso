#include "tft.h";

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

TftDisplay::TftDisplay() {}

void TftDisplay::initDisplay() {
  //pinMode(TFT_LED, OUTPUT);
  //digitalWrite(TFT_LED, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setTextWrap(true);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.println("Welcome to");
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2);
  tft.println("Coffeemaker");
}

void TftDisplay::message_print(String msg1, String msg2, int wait) {
#if defined(SERLOG)
  if (msg1 != "") { Serial.print(msg1 + " "); }
  if (msg2 != "") { Serial.print(msg2); }
  if ((msg1 != "") || (msg2 != "")) { Serial.println(""); }
#endif
  //digitalWrite(TFT_LED, HIGH);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  if (msg1 != "") {
    tft.println(msg1);
  }
  tft.setCursor(0, 30);
  tft.setTextSize(1);
  if (msg2 != "") {
    tft.println(msg2);
  }
  if (wait > 0) { 
    delay(wait);
      tft.fillScreen(ST7735_BLACK);
      //digitalWrite(TFT_LED, LOW);
  }
}

void TftDisplay::message_clear() {
  tft.fillScreen(ST7735_BLACK);
  //digitalWrite(TFT_LED, LOW);
}
