#ifndef OTAUPDATE_H
#define OTAUPDATE_H

#include <ESP8266httpUpdate.h>
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