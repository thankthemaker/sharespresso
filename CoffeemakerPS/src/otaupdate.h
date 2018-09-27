#ifndef OTAUPDATE_H
#define OTAUPDATE_H

#ifndef ESP32
 #include <ESP8266httpUpdate.h>
#else
 #include <ESP32httpUpdate.h>
#endif


#include "logging.h";
#include "settings.h"
#include "IDisplay.h"

class OTAUpdate {
    private:
        CoffeeLogger logger;
        IDisplay* oled;


    public:
        OTAUpdate(IDisplay *oled);
        void startUpdate();
};
#endif

