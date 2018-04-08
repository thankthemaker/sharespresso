#include "tft.h";

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

TftDisplay::TftDisplay() {}

void TftDisplay::initDisplay() {
  //pinMode(TFT_LED, OUTPUT);
  //digitalWrite(TFT_LED, HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
}

void TftDisplay::print_logo() {
  tft.fillScreen(ST7735_WHITE);
  this->bmpDraw("postbank.bmp", 40, 24);
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
  tft.setCursor(3, 3);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  if (msg1 != "") {
    tft.println(msg1);
  }
  tft.setCursor(3, 33);
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

void TftDisplay::message_print_scroll(String msg) {
    tft.fillScreen(ST7735_BLACK);
    Serial.println("Scroll message: " + msg);
    for(int index=120; index>0; index=index-3) {

      tft.setCursor(3, index+3);
      tft.setTextColor(ST7735_BLACK);
      tft.print(msg); 
      
      tft.setCursor(3, index);
      tft.setTextColor(ST7735_WHITE);
      tft.print(msg);  
        
      delay(90);
    }
}

void TftDisplay::message_clear() {
  tft.fillScreen(ST7735_BLACK);
  //digitalWrite(TFT_LED, LOW);
}

#define BUFFPIXEL 20

void TftDisplay::bmpDraw(char *filename, uint8_t x, uint8_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print("File not found");
    return;
  }

  // Parse BMP header
  if(this->read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print("File size: "); Serial.println(this->read32(bmpFile));
    (void)this->read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print("Header size: "); Serial.println(read32(bmpFile));
    bmpWidth  = this->read32(bmpFile);
    bmpHeight = this->read32(bmpFile);
    if(this->read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = this->read16(bmpFile); // bits per pixel
      Serial.print("Bit Depth: "); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (this->read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print("Image size: ");
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r,g,b));
          } // end pixel
        } // end scanline
        Serial.print("Loaded in ");
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t TftDisplay::read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t TftDisplay::read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}