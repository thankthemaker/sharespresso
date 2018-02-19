#include "otaupdate.h"

    OTAUpdate::OTAUpdate(IDisplay *oled) {
        this->oled = oled;
    }

    void OTAUpdate::startUpdate() {
        this->oled->message_print(F("Firmware update"), F("requested"), 0);

        t_httpUpdate_return ret = ESPhttpUpdate.update(OTA_UPDATE_URL);

        switch(ret) {
            case HTTP_UPDATE_FAILED:
                logger.log("HTTP_UPDATE_FAILED Error " + String(ESPhttpUpdate.getLastError()) + ", " + ESPhttpUpdate.getLastErrorString().c_str());
                this->oled->message_print(F("Update failed"), ESPhttpUpdate.getLastErrorString().c_str(), 0);
                break;

            case HTTP_UPDATE_NO_UPDATES:
                logger.log("HTTP_UPDATE_NO_UPDATES");
                this->oled->message_print(F("Firmware update"), F("No update available!"), 0);
                break;

            case HTTP_UPDATE_OK:
                logger.log("HTTP_UPDATE_OK");
                this->oled->message_print(F("Firmware update"), F("Update OK!"), 0);
              break;
        }
    }
