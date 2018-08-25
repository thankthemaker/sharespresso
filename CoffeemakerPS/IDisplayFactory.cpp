#include "IDisplay.h"

#if defined(DISPLAY_OLED)
 #include "oled.h";
#elif defined(DISPLAY_OLED_SPI)
 #include "oled_spi.h";
#elif defined(DISPLAY_TFT)
 #include "tft.h"
#endif

DisplayFactory* DisplayFactory::instance = 0;

DisplayFactory::DisplayFactory() {}

DisplayFactory* DisplayFactory::getInstance() {
    if (instance == 0)
    {
        instance = new DisplayFactory();
    }

    return instance;
}

IDisplay* DisplayFactory::createDisplay() {
#if defined(DISPLAY_OLED)
 return new OledDisplay();
#elif defined(DISPLAY_OLED_SPI)
 return new OledSpiDisplay();
#elif defined(DISPLAY_TFT)
 return new TftDisplay();
#endif
}

