#include "Arduino.h"

#ifndef SETTINGS_H_
 #include "settings.h"
#endif

class IDisplay {
    public:
        // pure virtual (abstract) method definitions
        virtual void init() = 0;
        virtual void message_print(String msg1, String msg2, int wait) = 0;
        virtual void message_clear() = 0;
};