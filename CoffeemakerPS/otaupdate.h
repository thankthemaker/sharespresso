#include <ESP8266httpUpdate.h>

#ifndef LOGGER_H_
  #include "logging.h";
#endif
#ifndef SETTINGS_H_
 #include "settings.h"
#endif
#ifndef OLED_H_
  #include "oled.h";
#endif

class OTAUpdate {
    private:
        CoffeeLogger logger;
        OledDisplay* oled;


    public:
        OTAUpdate(OledDisplay& oled);
        void startUpdate();
};